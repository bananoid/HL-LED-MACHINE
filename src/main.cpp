#include <Arduino.h>

// #define IS_SERVER // Comment for client mode

#include <Server.h>

#ifdef IS_SERVER

// #define _TASK_SLEEP_ON_IDLE_RUN
#include <TaskScheduler.h>
Scheduler runner;
// Callback methods prototypes
void sendParameters();
void sendSync();

#define SYNC_TIME_INTERVAL 16
// Tasks
// Task t1(16, TASK_FOREVER, &sendParameters, &runner, true);
Task t2(SYNC_TIME_INTERVAL, TASK_FOREVER, &sendSync, &runner, true);

void setup()
{
  Serial.begin(115200);

  ESPSortedBroadcast::ServerSingleton->begin();

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

#define _TASK_SLEEP_ON_IDLE_RUN
#define _TASK_STD_FUNCTION
#define _TASK_MICRO_RES
#include <TaskScheduler.h>

Scheduler runner;

#include "ClientMainController.h"
ClientMainController *mainController;

void setup()
{
  Serial.begin(115200);
  mainController = new ClientMainController(&runner);
  runner.startNow();
}

void loop()
{
  runner.execute();
}

#endif