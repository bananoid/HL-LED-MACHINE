#include "MainController.h"
#include <Arduino.h>
#include <LEDShaderSynth.h>

MainController::MainController(Scheduler *runner)
{
  CRGB *leds;
  int numOffLeds = 24;

  leds = new CRGB[numOffLeds];
  FastLED.addLeds<1, WS2812B, 18, GRB>(leds, numOffLeds);
  ledRenderer.begin(leds, numOffLeds);
  ledSynth = new LEDSynth::LEDSynth(numOffLeds, &ledRenderer, runner);

  LEDSynth::LEDShaderSynth *shader;

  shader = ledSynth->addLEDShaderSynth();
}
