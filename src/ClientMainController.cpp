#include "ClientMainController.h"

#include <Arduino.h>
// Scheduler runner;

// Task t1(16, TASK_FOREVER, &frameRender, &runner, true);
// Task t2(1000, TASK_FOREVER, &benckMarkFPS, &runner, true);
// Task t3(200, TASK_FOREVER, &clientUpdate, &runner, true);

// void ClientMainController::benckMarkFPS()
// {
//   Serial.print("Frame time :: ");
//   Serial.println(frameTime);
// }

// void ClientMainController::clientUpdate()
// {
//   int clientInx = ESPSortedBroadcast::ClientSingleton->clientId;
//   if (clientInx > 0)
//   {
//     Serial.print("Client index :: ");
//     Serial.println(clientInx);
//     t3.disable();
//     ledSynth->index = clientInx - 1;
//     return;
//   }
//   ESPSortedBroadcast::ClientSingleton->update();
//   Serial.println("Request Client Index");
// }

ClientMainController::ClientMainController(Scheduler *runner)
{
  this->runner = runner;

  ESPSortedBroadcast::ClientSingleton->begin();
  ESPSortedBroadcast::ClientSingleton->delegate = this;

  ledRenderer.begin();
  ledSynth = new LEDSynth::LEDSynth(&ledRenderer);

  // Task :: Client index request
  requestClientIndexTask.set(200000, TASK_FOREVER, [this]() {
    int clientInx = ESPSortedBroadcast::ClientSingleton->clientId;

    if (clientInx == 0)
    {
      Serial.print("requestClientIndexTask tick :: ");
      Serial.println(clientInx);
      ESPSortedBroadcast::ClientSingleton->requestClientIndex();
    }
    else
    {
      requestClientIndexTask.disable();
      renderCurrentIndex();
      frameRenderTask.delay(5000000);
    }
  });
  // runner->addTask(requestClientIndexTask);
  // requestClientIndexTask.enable();

  // Task :: Render led animation
  frameRenderTask.set(RENDER_FRAME_TIME, TASK_FOREVER, [this]() {
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
  ledSynth->syncTo(pos * 1000);
}
void ClientMainController::clientReceveClientIndex(ESPSortedBroadcast::SendIdAction data)
{
  // renderCurrentIndex();
}