#include "ServerMainController.h"

ServerMainController::ServerMainController(Scheduler *runner)
{
  this->runner = runner;

  sendSyncTask.set(TASK_MILLISECOND * SYNC_TIME_INTERVAL, TASK_FOREVER, [this]() {
    ESPSortedBroadcast::ServerSingleton->broadCastCurrentPosition();
  });
  runner->addTask(sendSyncTask);
  sendSyncTask.enable();
}
