#pragma once
#include <Peer.h>

#include "AOYAMA_TREE/COMMON/config.h"
#define _TASK_STD_FUNCTION
#include <TaskSchedulerDeclarations.h>

#include <OledScreen.h>

class BranchSlave : public ESPSortedBroadcast::Peer
{
public:
  // wifi
  void receiveDataCB(const uint8_t *mac, const uint8_t *incomingData, int len) override;

  void registerReceiveDataCB() override;

  void begin(int wifiChannel, ESPSortedBroadcast::PeerRecord *peerList, int nPeers, Scheduler *runner);
  // void update();

  OledScreen *screen;

  Task displayScreen;

  Task ping;
};

extern BranchSlave *BranchSlaveSingleton;
