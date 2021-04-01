#pragma once
#include <Peer.h>

#include "AOYAMA_TREE/COMMON/config.h"
#include "AOYAMA_TREE/COMMON/TrackerFactory.h"

#define _TASK_MICRO_RES
#define _TASK_STD_FUNCTION
#include <TaskSchedulerDeclarations.h>

#include <Tracker.h>
#include <Sequencer.h>
#include <PolyPinInstrumet.h>

using namespace HLMusicMachine;

class Branch : public ESPSortedBroadcast::Peer
{
private:
public:
  void registerReceiveDataCB() override;
  virtual void receiveFilteredDataCB(uint8_t type,
                                     uint8_t sourceId,
                                     uint8_t targetId,
                                     const uint8_t *mac,
                                     const uint8_t *incomingData,
                                     int len) override;

  void begin(int wifiChannel, ESPSortedBroadcast::PeerRecord *peerList, int nPeers, Scheduler *runner);

  Tracker *tracker;
  Track *track;
};

extern Branch *BranchSingleton;