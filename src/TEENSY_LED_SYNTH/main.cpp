#include <Arduino.h>

#define _TASK_OO_CALLBACKS
#define _TASK_MICRO_RES
#include <TaskScheduler.h>

Scheduler runner;

#include "MainController.h"
MainController *mainController;

void setup()
{
  Serial.begin(115200);

  mainController = new MainController(&runner);

  runner.startNow();
}

void loop()
{
  runner.execute();
  mainController->update();
}
