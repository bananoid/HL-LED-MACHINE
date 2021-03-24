#include <Arduino.h>
#include "TemplatePeer.h"
#include "config.h"
#include <Boards.h>

#include <TaskScheduler.h>

Scheduler runner;

#define BOARD_TYPES TREE, FLOWER, BRANCH, ROCK

board boardList[] = {
    {"3C:61:05:2F:A9:7C", "Flower", FLOWER},
    {"3C:61:05:2E:85:74", "Flower", FLOWER},
    {"24:0A:C4:ED:92:0C", "Tree", TREE},
    {"3C:61:05:2B:01:05", "Solenoid", BRANCH},
};

void setup()
{
  pinMode(2, OUTPUT);

  Serial.begin(115200);

  TemplatePeerSingleton->boardList = boardList;

  TemplatePeerSingleton->begin(WIFI_CHANNEL, &runner);

  runner.startNow();
}
void loop()
{
  runner.execute();

  digitalWrite(2, HIGH);
  delay(500);
  digitalWrite(2, LOW);
  delay(500);
}
