#include <Arduino.h>

#define _TASK_STD_FUNCTION
#include <TaskScheduler.h>

Scheduler runner;

#include "ServerMainController.h"
#include <Server.h>
ServerMainController *mainController;

void setup()
{
  Serial.begin(115200);

  ESPSortedBroadcast::ServerSingleton->begin();

  mainController = new ServerMainController(&runner);

  runner.startNow();
}
void loop()
{
  runner.execute();
}