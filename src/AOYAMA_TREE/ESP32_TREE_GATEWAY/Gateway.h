#pragma once
#include <Peer.h>

#include "AOYAMA_TREE/COMMON/config.h"
#define _TASK_STD_FUNCTION
#include <TaskSchedulerDeclarations.h>
#include <SerialMessenger.h>

#define OLEDSCREEN_DISABLED

#ifndef OLEDSCREEN_DISABLED
#include <OledScreen.h>
#endif

using namespace HLSerialMessanger;

class Gateway : public ESPSortedBroadcast::Peer, SerialMessengerDelegate
{
public:
  // wifi
  void receiveDataCB(const uint8_t *mac, const uint8_t *incomingData, int len) override;

  void registerReceiveDataCB() override;

  void begin(int wifiChannel, ESPSortedBroadcast::PeerRecord *peerList, int nPeers, Scheduler *runner);
  void update();
#ifndef OLEDSCREEN_DISABLED
  OledScreen *screen;
#endif
  Task displayScreen;

  Task ping;

  Task serialUpdateTask;

  // void serialMessengerReceiveMsg(BaseMessage *message) override;

  void serialMessengerReceiveData(const uint8_t *incomingData, int len) override;
};

extern Gateway *GatewaySingleton;
