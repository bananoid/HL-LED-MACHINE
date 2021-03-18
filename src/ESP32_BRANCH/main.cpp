#include <Arduino.h>

#define _TASK_STD_FUNCTION
#include <TaskScheduler.h>
#include "Branch.h"

Scheduler runner;

// #include "ServerMainController.h"
// #include <Server.h>
// ServerMainController *mainController;

void setup()
{
  Serial.begin(115200);

  BranchSingleton->begin();
  BranchSingleton->beginServer(); //TODO call begin (from parent) inside beginServer

  runner.startNow();
}
void loop()
{
  runner.execute();
  delay(1000);

  BranchSingleton->ping();

  // Serial.println(touchRead(13));
}
