#include "MainController.h"
#include <Arduino.h>

#define BOUD_RATE 1000000

MainController::MainController()
{
  pinMode(13, OUTPUT);

  midiControl = new MIDIControl();
  midiControl->delegate = this;

  audioControl = new HLAudioControl::AudioControl();
  audioControl->delegate = this;

  SerialMessengerSingleton->delegate = this;
}

void MainController::begin()
{
  midiControl->begin();
  audioControl->begin();

  Serial6.begin(BOUD_RATE);
  SerialMessengerSingleton->begin(&Serial6, BOUD_RATE);
}
void MainController::update()
{
  midiControl->update();
  audioControl->update();

  unsigned long curTime = millis();
  if (lastTime != curTime)
  {
    lastTime = curTime;

    if ((curTime) % 1000 == 0)
    {
      // Serial.println(curTime);
      // Message m;
      // m.type = 3;
      // SerialMessengerSingleton->sendMessage(&m);
    }
  }
  SerialMessengerSingleton->update();
}

void MainController::serialMessengerReceiveMsg(Message *message)
{
  Serial.printf("receve Message type: %i \n", message->type);
}

void MainController::midiControlReceiveMsg(ControlMsg *message)
{
  Serial.printf("Receive Message type :: %i - channel :: %i - id :: %i", message->type, message->channel, message->id);
  if (message->type == LEDSynthMessages::CONTROL_VALUE_MSG)
  {
    ControlValue cMsg;
    memcpy(&cMsg, message, sizeof(cMsg));

    Serial.printf(" - Value :: %f", cMsg.value);
  }
  else if (message->type == LEDSynthMessages::CONTROL_BUTTON_PRESS_MSG)
  {
    Serial.printf(" - Button press");
  }
  else if (message->type == LEDSynthMessages::CONTROL_BUTTON_RELEASE_MSG)
  {
    Serial.printf(" - Button release");
  }
  Serial.println();
}

void MainController::audioControlReceiveMsg(AudioSignalsMsg *message)
{
  // Serial.println(message->lowBand);
  analogWrite(13, message->lowBand * 255);
}