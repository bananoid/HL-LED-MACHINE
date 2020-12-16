#include <Arduino.h>

#define _TASK_STD_FUNCTION
#include <TaskScheduler.h>

Scheduler runner;

#include "ClientMainController.h"
ClientMainController *mainController;

void setup()
{
  Serial.begin(115200);

  ESPSortedBroadcast::ClientSingleton->begin();

  mainController = new ClientMainController(&runner);

  runner.startNow();
}
// ----------------------------------

void loop()
{
  runner.execute();
}
