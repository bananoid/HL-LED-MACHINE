#pragma once
#include <Peer.h>

#include "AOYAMA_TREE/COMMON/config.h"
#define _TASK_STD_FUNCTION
#define _TASK_OO_CALLBACKS
#include <TaskSchedulerDeclarations.h>

#include <OledScreen.h>

#include <PinInstrument.h>

using namespace HLMusicMachine;

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

  PinIntrument *instrument;
};

extern BranchSlave *BranchSlaveSingleton;
