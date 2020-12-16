#include "ClientMainController.h"
#include <Arduino.h>

ClientMainController::ClientMainController(Scheduler *runner)
{
  this->runner = runner;

  // ESPSortedBroadcast::ClientSingleton->begin();
  ESPSortedBroadcast::ClientSingleton->delegate = this;

  ledRenderer.begin();
  ledSynth = new LEDSynth::LEDSynth(&ledRenderer);

  // Task :: Client index request
  requestClientIndexTask.set(TASK_MILLISECOND * 1000, TASK_FOREVER, [this]() {
    int clientInx = ESPSortedBroadcast::ClientSingleton->clientId;

    if (clientInx == 0)
    {
      ESPSortedBroadcast::ClientSingleton->requestClientIndex();
    }
    else
    {
      requestClientIndexTask.disable();
      renderCurrentIndex();
      frameRenderTask.delay(TASK_SECOND * 4);
    }
  });
  runner->addTask(requestClientIndexTask);
  requestClientIndexTask.enable();

  // Task :: Render led animation
  frameRenderTask.set(TASK_MILLISECOND * 16, TASK_FOREVER, [this]() {
    this->frameRender();
  });
  runner->addTask(frameRenderTask);
  frameRenderTask.enable();
}

void ClientMainController::frameRender()
{
  unsigned long curTime = micros();
  ledSynth->update();
  frameTime = micros() - curTime;
}

void ClientMainController::renderCurrentIndex()
{
  int clientInx = ESPSortedBroadcast::ClientSingleton->clientId;

  for (size_t i = 0; i < LS_NUM_LEDS_PER_STRIP; i++)
  {
    GFXUtils::fRGB color;
    if (i + 1 <= clientInx)
    {
      color = GFXUtils::fRGB(0, 0, 1);
    }
    else
    {
      color = GFXUtils::fRGB(1, 0, 0);
    }
    ledRenderer.setPixel(i, color);
  }
  ledRenderer.show();
}

void ClientMainController::clientReceveSyncAction(ESPSortedBroadcast::SyncAction data)
{
  unsigned long pos = data.position;
  ledSynth->syncTo(pos);
}
void ClientMainController::clientReceveClientIndex(ESPSortedBroadcast::SendIdAction data)
{
  ledSynth->index = data.id - 1; // Start index from 0 :: data id start from 1
}