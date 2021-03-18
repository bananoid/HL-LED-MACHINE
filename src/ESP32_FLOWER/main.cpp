#include <Arduino.h>

#define _TASK_STD_FUNCTION
#include <TaskScheduler.h>
#include "Flower.h"
#include "TouchSensor.h"
#include "GyroSensor.h"

Scheduler runner;
GyroSensor gyroSensor;
TouchSensor touchSensor;

// #include "ServerMainController.h"
// #include <Server.h>
// ServerMainController *mainController;

void setup()
{
  Serial.begin(115200);

  FlowerSingleton->begin();
  FlowerSingleton->beginServer(); //TODO call begin (from parent) inside beginServer

  gyroSensor.begin();

  runner.startNow();
}
void loop()
{
  runner.execute();
  delay(1000);

  // FlowerSingleton->ping();

  touchSensor.update();

  if (touchSensor.touchReads[0] < 50)
  {
    Serial.println("Touch A!");
    int targetId = 2;
    FlowerTouchMessage message = {};
    message.sourceId = FlowerSingleton->boardInfo.boardId;
    message.targetId = targetId;

    FlowerSingleton->broadcastData((uint8_t *)&message, sizeof(FlowerTouchMessage));
  }

  if (touchSensor.touchReads[1] < 50)
  {
    /* code */
    Serial.println("Touch B!");
    int targetId = 3;
    FlowerTouchMessage message = {};
    message.sourceId = FlowerSingleton->boardInfo.boardId;
    message.targetId = targetId;

    FlowerSingleton->broadcastData((uint8_t *)&message, sizeof(FlowerTouchMessage));
  }

  if (touchSensor.touchReads[2] < 50)
  {
    /* code */
    Serial.println("Touch C!");
    int targetId = 3;
    BranchStateMessage message = {};
    message.sourceId = FlowerSingleton->boardInfo.boardId;
    message.targetId = targetId;

    FlowerSingleton->broadcastData((uint8_t *)&message, sizeof(BranchStateMessage));
  }
}
