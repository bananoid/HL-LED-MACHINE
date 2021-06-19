#pragma once

#include "config.h"
#include <TaskSchedulerDeclarations.h>

#include <Encoder.h>
#include <Bounce2.h>

#define ENCODER_LEFT_PIN_SW 2
#define ENCODER_LEFT_PIN_A 3
#define ENCODER_LEFT_PIN_B 4
#define ENCODER_RIGHT_PIN_SW 30
#define ENCODER_RIGHT_PIN_A 31
#define ENCODER_RIGHT_PIN_B 32

class UI
{
private:
public:
  Task updateTask;

  Encoder *leftEncoder;
  Bounce *leftEncoderButton;

  Encoder *rightEncoder;
  Bounce *rightEncoderButton;

  void begin(Scheduler *runner);
  void update();
  void draw();
};

extern UI *ui;