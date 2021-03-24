#pragma once
#include <Peer.h>

#include "config.h"
#include <TaskSchedulerDeclarations.h>

class TemplatePeer : public ESPSortedBroadcast::Peer
{
  public:
  void receiveDataCB(const uint8_t *mac, const uint8_t *incomingData, int len) override;

  void registerReceiveDataCB() override;

  void begin(int wifiChannel, Scheduler *runner);
};

extern TemplatePeer *TemplatePeerSingleton;