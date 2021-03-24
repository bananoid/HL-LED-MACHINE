#include "MainController.h"
#include <Arduino.h>
#include <LEDShader.h>
#include <LEDShaderSynth.h>
#include <LEDShaderDiffusion.h>

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
  shader->targetState->scale = 0.1;
  shader->targetState->que = 2.;

  shader = ledSynth->addLEDShaderSynth(LEDSynth::LEDShader::ADD);
  shader->targetState->speed = -0.2;
  shader->targetState->hue = 0;
  shader->targetState->hueRad = 0.1;
  shader->targetState->scale = 0.1;
  shader->targetState->intensity = 0.01;
  shader->targetState->saturation = 0.9;

  difShader = ledSynth->addLEDShaderDiffusion(LEDSynth::LEDShader::ADD);

  //Trig Button
  trigButton.attach(9, INPUT_PULLUP); // USE EXTERNAL PULL-UP
  trigButton.interval(5);
  trigButton.setPressedState(LOW);
}

void MainController::update()
{
  trigButton.update();
  if (trigButton.pressed())
  {
    float pos = LEDSynth::GFXUtils::rnd(millis());
    // pos = 0.99;
    if (LEDSynth::GFXUtils::rnd(millis() + 100) > 0.5)
    {
      difShader->trig(pos, {0.9, 0.3, 0.1});
    }
    else
    {
      difShader->trig(pos, {0.1, 0.5, 0.5});
    }
  }
}