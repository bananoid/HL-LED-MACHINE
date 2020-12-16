#ifndef HL_SRC_SERVERMAINCONTROLLER
#define HL_SRC_SERVERMAINCONTROLLER

#define SYNC_TIME_INTERVAL 2000

#include <Arduino.h>
#include <Server.h>

#define _TASK_STD_FUNCTION
// #define _TASK_MICRO_RES
#include <TaskSchedulerDeclarations.h>

class ServerMainController
{
private:
public:
  Task sendSyncTask;

  ServerMainController(Scheduler *runner);
  Scheduler *runner;
};
#endif /* HL_SRC_SERVERMAINCONTROLLER */
