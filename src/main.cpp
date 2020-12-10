#include <Arduino.h>

#define IS_SERVER // Comment for client mode

#define _TASK_STD_FUNCTION
// #define _TASK_MICRO_RES
#include <TaskScheduler.h>

Scheduler runner;

#ifdef IS_SERVER

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

#else

#include "ClientMainController.h"
ClientMainController *mainController;

void setup()
{
  Serial.begin(115200);

  ESPSortedBroadcast::ClientSingleton->begin();

  mainController = new ClientMainController(&runner);

  runner.startNow();
}
#endif

void loop()
{
  runner.execute();
}