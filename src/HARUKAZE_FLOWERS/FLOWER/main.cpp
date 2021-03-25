#include <Arduino.h>

#define _TASK_STD_FUNCTION
#include <TaskScheduler.h>

#include "HARUKAZE_FLOWERS/COMMON/Messages.h"
#include "HARUKAZE_FLOWERS/COMMON/config.h"

#include "Flower.h"

using namespace ESPSortedBroadcast;

Scheduler runner;

PeerRecord peerList[] = PEER_LIST;

void setup()
{
  // pinMode(18, OUTPUT);
  // pinMode(19, OUTPUT);
  Serial.begin(115200);

  FlowerSingleton->begin(WIFI_CHANNEL, peerList, N_PEERS, &runner);

  runner.startNow();
}
void loop()
{
  runner.execute();
  FlowerSingleton->screen->sayHello(2);
}
