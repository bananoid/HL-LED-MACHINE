#include "MainController.h"
#include <Arduino.h>
#include <LEDShader.h>
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
  shader->targetState->speed = 0.13;
  shader->targetState->hue = 0.5;
  shader->targetState->hueRad = 0;

  shader = ledSynth->addLEDShaderSynth(LEDSynth::LEDShader::ADD);
  shader->targetState->speed = -0.2;
  shader->targetState->hue = 0;
  shader->targetState->hueRad = 0;
  shader->targetState->saturation = 0.5;
}
