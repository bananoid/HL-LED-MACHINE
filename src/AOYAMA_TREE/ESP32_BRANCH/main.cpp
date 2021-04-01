#include <Arduino.h>

#define _TASK_MICRO_RES
#define _TASK_STD_FUNCTION
#include <TaskScheduler.h>

#include "AOYAMA_TREE/COMMON/Messages.h"
#include "AOYAMA_TREE/COMMON/config.h"

#include "Branch.h"
#include <WiFi.h>

using namespace ESPSortedBroadcast;

Scheduler runner;

PeerRecord peerList[] = PEER_LIST;

void setup()
{
  Serial.begin(115200);

  BranchSingleton->begin(WIFI_CHANNEL, peerList, N_PEERS, &runner);

  runner.startNow();
}
void loop()
{
  runner.execute();
  // Serial.println(WiFi.macAddress());
}
