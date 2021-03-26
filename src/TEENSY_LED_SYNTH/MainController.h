#pragma once

#include <Arduino.h>

#include <FastLED.h>
#include <FastLEDRenderer.h>
#include <LEDSynth.h>

#define _TASK_OO_CALLBACKS
#define _TASK_MICRO_RES
#include <TaskSchedulerDeclarations.h>

#include <Bounce2.h>

class MainController
{
private:
public:
  MainController(Scheduler *runner);
  LEDSynth::FastLEDRenderer ledRenderer;
  LEDSynth::LEDSynth *ledSynth;

  LEDSynth::LEDShaderDiffusion *difShader;

  Bounce2::Button trigButton = Bounce2::Button();

  void update();
};