#include <Arduino.h>

#include "Flower.h"
#include "TouchSensor.h"
#include "GyroSensor.h"
#include "AOYAMA_TREE/COMMON/Messages.h"
#include "AOYAMA_TREE/COMMON/Screen.h"
#include "AOYAMA_TREE/COMMON/config.h"

#include <TaskScheduler.h>

Scheduler runner;
GyroSensor gyroSensor;
TouchSensor touchSensor;
// Screen screen;

// #include "ServerMainController.h"
// #include <Server.h>
// ServerMainController *mainController;

board boardList[] = {
    {"3C:61:05:2F:A9:7C", "Flower", FLOWER},
    {"3C:61:05:2E:85:74", "Flower", FLOWER},
    {"24:0A:C4:ED:92:0C", "Tree", TREE},
    {"3C:61:05:2B:01:05", "Solenoid", BRANCH},
};

void setup()
{
  Serial.begin(115200);

  FlowerSingleton->boardList = boardList;

  FlowerSingleton->begin(WIFI_CHANNEL, &runner);
  FlowerSingleton->screen->begin();
  // FlowerSingleton->beginServer(); //TODO call begin (from parent) inside beginServer

  gyroSensor.begin();

  runner.startNow();
}
void loop()
{
  runner.execute();
  // delay(1000);
  pinMode(2, OUTPUT);
  // FlowerSingleton->ping();
  // screen.clear();
  // screen.sayHello(0);
  // screen.displayScreen();

  touchSensor.update();

  // FlowerSingleton->screen->clear();
  FlowerSingleton->screen->print(FlowerSingleton->boardInfo.boardName, 0);
  FlowerSingleton->screen->print(FlowerSingleton->boardInfo.macAddress, 8);
  // screen.sayHello(0);

  Serial.println(FlowerSingleton->boardInfo.boardName);

  if (touchSensor.touchReads[0] < 50)
  {
    Serial.println("Touch A!");
    int targetId = 1;
    FlowerTouchMessage message = {};
    message.sourceId = FlowerSingleton->boardInfo.boardId;
    message.targetId = targetId;

    FlowerSingleton->broadcastData((uint8_t *)&message, sizeof(FlowerTouchMessage));

    FlowerSingleton->screen->print("Sending data to 1", 16);
  }

  if (touchSensor.touchReads[1] < 50)
  {
    /* code */
    Serial.println("Touch B! Sending ping to 1");
    int targetId = 2;
    FlowerTouchMessage message = {};
    message.sourceId = FlowerSingleton->boardInfo.boardId;
    message.targetId = targetId;

    FlowerSingleton->broadcastData((uint8_t *)&message, sizeof(FlowerTouchMessage));

    FlowerSingleton->screen->print("Sending data to 2", 24);
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

    FlowerSingleton->screen->print("Sending data to 3", 32);
  }

  // FlowerSingleton->screen->displayScreen();
}
