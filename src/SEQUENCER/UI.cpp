#include "UI.h"
#include "config.h"

UI::UI(Scheduler *runner) : Task(16 * TASK_MILLISECOND, TASK_FOREVER, runner, true)
{
  encoder = new Encoder(ENCODER_PIN_A, ENCODER_PIN_B);
  encoderOldPosition = -999;

  encoderButton = new Bounce();
  encoderButton->attach(ENCODER_PIN_BUTTON, INPUT);
  encoderButton->interval(25);

  for (int i = 0; i < NUMBER_OF_INSTRUMENTS; i++)
  {
    instrumentButtons[i] = new Bounce();
    instrumentButtons[i]->attach(buttonPins[i], INPUT_PULLUP);
    instrumentButtons[i]->interval(25);
  }

  FastLED.addLeds<NUM_LED_STRIPES, WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);

  mainMode = master;
  instrumentMode = events;
  masterMode = bpm;

  FastLED.setBrightness(255);
  FastLED.setMaxPowerInMilliWatts(10000000);
  FastLED.setDither(DISABLE_DITHER);
};

void UI::update()
{
  encoderButton->update();
  bool encoderButtonState = encoderButton->read();

  int encoderPosition = encoder->read() / 5;
  bool encoderPositionChange = false;
  int encoderIncrement = 0;

  if (encoderPosition != encoderOldPosition)
  {
    int delta = encoderOldPosition - encoderPosition;

    if (delta > 0)
    {
      encoderIncrement = 1;
    }
    else if (delta < 0)
    {
      encoderIncrement = -1;
    }

    encoderOldPosition = encoderPosition;
    encoderPositionChange = true;
  }

  int encoderSnapPosition = encoderPosition / encoderSnapPositonSize;
  bool encoderSnapPositionChange = false;
  int encoderSnapIncrement = 0;

  if (encoderSnapPosition != encoderOldSnapPositon)
  {
    int delta = encoderOldSnapPositon - encoderSnapPosition;

    if (delta > 0)
    {
      encoderSnapIncrement = 1;
    }
    else if (delta < 0)
    {
      encoderSnapIncrement = -1;
    }

    encoderOldSnapPositon = encoderSnapPosition;
    encoderSnapPositionChange = true;

    // Serial.printf("snap -> pos:%i inc:%i\n",
    //               encoderSnapPosition, encoderSnapIncrement);
  }

  bool encoderButtonChange = encoderButton->changed();

  if (encoderButtonChange)
  {
    if (encoderButtonState == LOW)
    {
      encoderButtonPress = true;
    }
    else
    {
      encoderButtonPress = false;
    }
  }

  if (
      encoderButtonPress &&
      encoderSnapPositionChange)
  {
    encoderPressRotationMode = true;
    Serial.printf("encoderPressRotationMode %i\n", encoderSnapIncrement);
    if (encoderIncrement == 1)
    {
      selectNextMainMode();
    }
    else
    {
      selectPrevMainMode();
    }
  }

  if (
      encoderButtonChange &&
      encoderButtonState == HIGH &&
      !encoderPressRotationMode)
  {
    Serial.println("release! : changing main mode");

    if (mainMode == master)
    {
      selectNextMasterMode();
    }
    else
    {
      selectNextInstrumentMode();
    }
  }

  if (
      encoderButtonChange &&
      encoderButtonState == HIGH &&
      encoderPressRotationMode)
  {
    Serial.println("release! : end encoderPressRotationMode");
    encoderPressRotationMode = false;
  }

  if (
      encoderPositionChange &&
      !encoderPressRotationMode &&
      !encoderButtonPress)
  {
    onEncoderRotate(encoderIncrement);
  }

  // instrument buttons
  for (int i = 0; i < NUMBER_OF_INSTRUMENTS; i++)
  {
    instrumentButtons[i]->update();
    if (instrumentButtons[i]->changed())
    {
      int buttonState = instrumentButtons[i]->read();
      if (buttonState == HIGH)
      {
        Serial.printf("click! on button %i\n", i);
        Instrument *instrument = delegate->getInstrumentForIndex(i);
        // Serial.printf("release! on button %i is play:%i\n", i , instrument->isPlaying);

        if (mainMode == i)
        {
          instrument->togglePlayPause();
          isUIInvalid = true;
        }
        else
        {
          selectMainMode(i);
        }
      }
    }
  }

  // Time Step
  if (delegate->getCurrentPlayStepIndex() != prevPlayStepIndex)
  {
    prevPlayStepIndex = delegate->getCurrentPlayStepIndex();
    isUIInvalid = true;
  }
}

bool UI::Callback()
{
  drawUI();
}

void UI::drawUI()
{

  if (!isUIInvalid)
  {
    return;
  }

  FastLED.clear();

  if (mainMode < mainModeCount - 1)
  {
    // Instrument View ////////////////////////////

    drawInstrument();
  }
  else
  {
    // Master View ////////////////////////////
    drawMaster();
  }

  FastLED.show();
  FastLED.show();

  isUIInvalid = false;
}

void UI::drawInstrument()
{
  CRGB color;
  Instrument *instrument = delegate->getInstrumentForIndex(mainMode);

  float h = (float)mainMode / (float)(mainModeCount - 1) * 0.95;

  float intensity = (float)(instrumentMode + 1) / (float)(instrumentModeCount);

  // float hOff = (float)(instrumentMode + 1) / (float)(instrumentModeCount)*0.1;
  // intensity = 1;
  // h += hOff;

  if (instrument->isPlaying)
  {
    color = CHSV(h * 255, 255, intensity * 255);
  }
  else
  {
    color = CHSV(h * 255, 0.6 * 255, intensity * 0.4 * 255);
  }

  for (int i = 0; i < NUM_LEDS; i++)
  {
    bool isOn = instrument->isEuclidianSeq(i);

    if (prevPlayStepIndex != i)
    {
      leds[i] = isOn ? color : CRGB(0, 0, 0);
    }
    else
    {
      leds[i] = CRGB(255, 255, 255);
    }
  }
}
void UI::drawMaster()
{
  CRGB color;
  float pos = 0;

  float saturation = 0.0f;

  if (masterMode == bpm)
  {
    pos = delegate->getBpmPercentage() * NUM_LEDS;
  }
  else if (masterMode == trigTime)
  {
    pos = delegate->getTrigTimePercentage() * NUM_LEDS;
    saturation = 1.0f;

  }else if (masterMode == trigPWM){
    pos = delegate->getTrigPWMPercentage() * NUM_LEDS;

    saturation = 0.5f;
  }

  int posInx = pos;

  float aa = fmodf(pos, 1.0f);

  

  for (int i = 0; i < NUM_LEDS; i++)
  {
    if (prevPlayStepIndex != i)
    {
      float hue = (float)i / NUM_LEDS;
      if (posInx == i)
      {
        color = CHSV(hue * 255, saturation * 255, aa * 255);
      }
      else if (i < posInx)
      {
        color = CHSV(hue * 255, saturation * 255, 255);
      }
      else
      {
        color = CRGB(0, 0, 0);
      }
    }
    else
    {
      color = CRGB(255, 0, 0);
    }

    leds[i] = color;
  }
}

void UI::selectMainMode(MainMode mode)
{
  mainMode = mode;
  isUIInvalid = true;
}

void UI::selectNextMainMode()
{
  mainMode++;
  if (mainMode >= mainModeCount)
  {
    mainMode = 0;
  }
  isUIInvalid = true;
};

void UI::selectPrevMainMode()
{
  mainMode--;
  if (mainMode < 0)
  {
    mainMode = mainModeCount - 1;
  }
  isUIInvalid = true;
};

void UI::selectNextInstrumentMode()
{
  instrumentMode++;
  if (instrumentMode >= instrumentModeCount)
  {
    instrumentMode = 0;
  }
  isUIInvalid = true;
};

void UI::selectNextMasterMode()
{
  masterMode++;
  if (masterMode >= masterModeCount)
  {
    masterMode = 0;
  }
  isUIInvalid = true;
};

void UI::onEncoderRotate(int increment)
{
  // Serial.printf("onEncoderRotate %i\n", increment);

  if (mainMode < mainModeCount - 1)
  {
    Instrument *instrument = delegate->getInstrumentForIndex(mainMode);

    if (instrumentMode == events)
    {
      instrument->events += increment;
      instrument->events = constrain(instrument->events, 1, 16);
    }
    else if (instrumentMode == steps)
    {
      instrument->steps += increment;
      instrument->steps = constrain(instrument->steps, 1, 16);
    }
    else if (instrumentMode == offset)
    {
      instrument->offset += increment;
      instrument->offset = constrain(instrument->offset, 0, 16);
    }
  }
  else if (mainMode == master)
  {
    if (masterMode == bpm)
    {
      delegate->increaseBpm(increment);
    }
    else if(masterMode == trigTime)
    {
      delegate->increaseTrigTime(increment);
    }else{
      delegate->increaseTrigPWM(increment);
    }
  }

  isUIInvalid = true;
}
