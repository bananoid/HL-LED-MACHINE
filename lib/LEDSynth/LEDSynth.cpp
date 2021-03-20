#include "LEDSynth.h"

#include <Arduino.h>

namespace LEDSynth
{

  LEDSynth::LEDSynth(int numberOfPixel, LEDStrips::LEDStripsRenderer *renderer, Scheduler *runner) : Task(16 * TASK_MILLISECOND, TASK_FOREVER, runner, true)
  {
    this->renderer = renderer;
    this->numberOfPixel = numberOfPixel;
  }

  bool LEDSynth::Callback()
  {
    update();
  }

  void LEDSynth::update()
  {
    unsigned long curTime = millis();
    position += (curTime - lastFrameTime);
    lastFrameTime = curTime;

    float t = position / 1000.0f;
    // t *= 0.1;
    // float oscA;
    float oscB;
    float phase;

    GFXUtils::fRGB color = GFXUtils::fRGB(1, 1, 1);

    int realNumOffPix = 16;

    for (size_t i = 0; i < numberOfPixel; i++)
    {
      phase = (i + index * realNumOffPix) * 0.1f;

      // oscA = sinf(fmodf(1.0 + fmodf(t * 0.35f + phase * 3.243, TWO_PI), TWO_PI)) * 0.1 + 1;
      // oscA = oscA * oscA * oscA;

      // oscB = sinf(fmodf(1.0 + fmodf(t * 1.521354f + phase * 5.43123, TWO_PI), TWO_PI)) * 0.5 + 0.5;
      // oscB = oscB * oscB * oscB;

      float x = t * 0.145;
      oscB = GFXUtils::GFXUtils::snoise(x);

      color = GFXUtils::GFXUtils::hsv(x * 0.012355, 1, oscB);
      renderer->setPixel(i, color);
    }

    renderer->show();
  }

  void LEDSynth::syncTo(unsigned long position) //position in ms
  {
    long delataPosition = this->position - position;

    // Serial.print("curPos :: ");
    // Serial.print(this->position);
    // Serial.print(" - recPos :: ");
    // Serial.print(position);
    // Serial.print(" - deltaPos :: ");
    // Serial.println(delataPosition);

    this->position = position;
  }

} // namespace LEDSynth
