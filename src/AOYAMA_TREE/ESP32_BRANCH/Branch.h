#pragma once
#include <Peer.h>
#include "AOYAMA_TREE/COMMON/Screen.h"

#include "AOYAMA_TREE/COMMON/config.h"
#include <TaskSchedulerDeclarations.h>

#include <Sequencer.h>
#include <Track.h>
#include <EuclideanSequence.h>
#include <PinInstrument.h>

using namespace HLSequencer;

class Branch : public ESPSortedBroadcast::Peer
{
private:
public:
  // void register_recv_cb();
  void receiveDataCB(const uint8_t *mac, const uint8_t *incomingData, int len) override;

  void registerReceiveDataCB() override;

  void begin(int wifiChannel, Scheduler *runner);

  Sequencer *sequencer;
  Screen *screen;
};

extern Branch *BranchSingleton;