#include <Arduino.h>

#include "Branch.h"
#include "AOYAMA_TREE/COMMON/Messages.h"
#include "AOYAMA_TREE/COMMON/config.h"

#include <TaskScheduler.h>

Scheduler runner;

board boardList[] = {
    {"3C:61:05:2F:A9:7C", "Flower", FLOWER},
    {"3C:61:05:2E:85:74", "Flower", FLOWER},
    // {"24:0A:C4:ED:92:0C", "Tree", TREE},
    {"3C:61:05:2B:01:04", "Branch", BRANCH},
};

void setup()
{
  Serial.begin(115200);

  BranchSingleton->boardList = boardList;

  BranchSingleton->begin(WIFI_CHANNEL, &runner);

  runner.startNow();
}
void loop()
{
  runner.execute();
  pinMode(2, OUTPUT);
}
