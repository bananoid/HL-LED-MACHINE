#include <Arduino.h>

#define _TASK_STD_FUNCTION
#include <TaskScheduler.h>

#include "HARUKAZE_FLOWERS/COMMON/config.h"

#include <WiFi.h>
#include <Peer.h>
#include "Gateway.h"

using namespace ESPSortedBroadcast;

Scheduler runner;

PeerRecord peerList[] = PEER_LIST;

void setup()
{
  pinMode(2, OUTPUT);

  Serial.begin(115200);
  GatewaySingleton->begin(WIFI_CHANNEL, peerList, N_PEERS, &runner);
}
void loop()
{
  runner.execute();
  GatewaySingleton->screen->sayHello(2);
  GatewaySingleton->update();
}
