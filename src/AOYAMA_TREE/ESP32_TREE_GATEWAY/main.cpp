#define _TASK_STD_FUNCTION
#include <TaskScheduler.h>

#include <Arduino.h>
#include "Gateway.h"
#include "config.h"
#include <Boards.h>
#include <WiFi.h>

Scheduler runner;

board boardList[] = {
    {"3C:61:05:2A:A0:50", "Gateway", TREE},
    {"3C:61:05:2E:85:74", "Flower", FLOWER},
    {"3C:61:05:2F:A9:7C", "Flower", FLOWER},
    {"24:0A:C4:ED:92:0C", "Tree", TREE},
    {"3C:61:05:2B:01:05", "Solenoid", BRANCH},

};

void setup()
{
  pinMode(2, OUTPUT);

  Serial.begin(115200);

  GatewaySingleton->boardList = boardList;

  GatewaySingleton->begin(WIFI_CHANNEL, &runner);
  GatewaySingleton->screen->clearScreen();
  GatewaySingleton->screen->println(GatewaySingleton->boardInfo.boardName, 0);
  GatewaySingleton->screen->println(GatewaySingleton->boardInfo.macAddress, 1);
}
void loop()
{
  runner.execute();

  GatewaySingleton->screen->sayHello(2);
}
