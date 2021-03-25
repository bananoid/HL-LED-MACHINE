#include <Arduino.h>

#define _TASK_STD_FUNCTION
#include <TaskScheduler.h>

#include "AOYAMA_TREE/COMMON/config.h"

#include <WiFi.h>
#include <Peer.h>
#include "BranchSlave.h"

using namespace ESPSortedBroadcast;

Scheduler runner;

PeerRecord peerList[] = PEER_LIST;

void setup()
{
  pinMode(2, OUTPUT);

  Serial.begin(115200);
  BranchSlaveSingleton->begin(WIFI_CHANNEL, peerList, N_PEERS, &runner);

  runner.startNow();
}
void loop()
{
  runner.execute();
  BranchSlaveSingleton->screen->sayHello(2);
}
