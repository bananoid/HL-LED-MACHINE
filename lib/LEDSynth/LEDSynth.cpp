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
    float t = micros() / 1000000.0f;
    float oscA;
    // float oscB;
    float phase;

    GFXUtils::fRGB color = GFXUtils::fRGB(1, 1, 1);

    for (size_t i = 0; i < LS_NUM_LEDS_PER_STRIP; i++)
    {
      phase = ((float)i) / ((float)LS_NUM_LEDS_PER_STRIP);
      oscA = sinf(t * 1.5f + (phase * TWO_PI) / 300.0f) * 0.5 + 0.5;
      // oscA = powf(oscA, 3);
      // color = GFXUtils::fRGB(oscA, 0, 0);
      color = GFXUtils::GFXUtils::hsv(phase + t * 0.1, 0.8, oscA);
      renderer->setPixel(i, color);
    }
    renderer->show();
  }

} // namespace LEDSynth
