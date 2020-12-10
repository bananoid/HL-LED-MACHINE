#include <Arduino.h>

// #define IS_SERVER // Comment for client mode

#ifdef IS_SERVER

#include <TaskScheduler.h>
Scheduler runner;

void sendParameters();
void sendSync();

#define SYNC_TIME_INTERVAL 2000
// Tasks
// Task t1(16, TASK_FOREVER, &sendParameters, &runner, true);
Task t2(SYNC_TIME_INTERVAL, TASK_FOREVER, &sendSync, &runner, true);

#include <Server.h>

void setup()
{
  Serial.begin(115200);

  ESPSortedBroadcast::ServerSingleton->begin();
  delay(2000);
  runner.startNow();
}

void loop()
{
  runner.execute();
}

void sendParameters()
{
  ESPSortedBroadcast::ServerSingleton->update();
}

void sendSync()
{
  ESPSortedBroadcast::ServerSingleton->broadCastCurrentPosition();
}
#else

#include "ClientMainController.h"
ClientMainController *mainController;

#define _TASK_STD_FUNCTION
// #define _TASK_MICRO_RES
#include <TaskScheduler.h>

Scheduler runner;

void setup()
{
  Serial.begin(115200);

  ESPSortedBroadcast::ClientSingleton->begin();

  mainController = new ClientMainController(&runner);

  runner.startNow();
}

void loop()
{
  runner.execute();
}

#endif