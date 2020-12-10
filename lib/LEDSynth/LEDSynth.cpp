#include "LEDSynth.h"

#include <Arduino.h>

namespace LEDSynth
{

  LEDSynth::LEDSynth(LEDStrips::LEDStripsRenderer *renderer)
  {
    this->renderer = renderer;
  }

  void LEDSynth::update()
  {
    unsigned long curTime = millis();
    position += (curTime - lastFrameTime);
    lastFrameTime = curTime;

    float t = position / 1000.0f;
    // t *= 0.1;
    float oscA;
    // float oscB;
    float phase;

    GFXUtils::fRGB color = GFXUtils::fRGB(1, 1, 1);

    int realNumOffPix = 16;

    for (size_t i = 0; i < LS_NUM_LEDS_PER_STRIP; i++)
    {
      phase = (i + index * realNumOffPix) * 0.1f;
      oscA = sinf(fmodf(1.0 + fmodf(t * 1.5f + phase * 2.043, TWO_PI), TWO_PI)) * 0.5 + 0.5;
      oscA = oscA * oscA * oscA;
      color = GFXUtils::GFXUtils::hsv(phase * 0.1 + t * 0.012345, 0.8, oscA);
      renderer->setPixel(i, color);
    }

    renderer->show();
  }

  void LEDSynth::syncTo(unsigned long position) //position in ms
  {
    long delataPosition = this->position - position;

    Serial.print("curPos :: ");
    Serial.print(this->position);
    Serial.print(" - recPos :: ");
    Serial.print(position);
    Serial.print(" - deltaPos :: ");
    Serial.println(delataPosition);

    this->position = position;
  }

} // namespace LEDSynth
