#include "Branch.h"
#include "AOYAMA_TREE/COMMON/Messages.h"

Branch *BranchSingleton = new Branch();

void Branch::begin(int wifiChannel, ESPSortedBroadcast::PeerRecord *peerList, int nPeers, Scheduler *runner)
{
  ESPSortedBroadcast::Peer::begin(wifiChannel, peerList, nPeers);

  tracker = new Tracker(runner);
  track = TrackerFactory::buildTrackWithInstrument(tracker, new PinIntrument(25, runner)); // TODO: Make PolyPin instriment 32 33 25
  tracker->clock->play();
  track->play();
}

void Branch::registerReceiveDataCB()
{
  esp_now_register_recv_cb([](const uint8_t *macaddr, const uint8_t *incomingData, int len) {
    BranchSingleton->receiveDataCB(macaddr, incomingData, len);
  });
}

void Branch::receiveFilteredDataCB(uint8_t messageType, uint8_t sourceId, uint8_t targetId, const uint8_t *mac, const uint8_t *incomingData, int len)
{
  switch (messageType)
  {

  case CLOCK_SYNC:
  {
    ClockSyncMessage msg;
    memcpy(&msg, incomingData, sizeof(ClockSyncMessage));
    Serial.printf("CLOCK_SYNC %i\n", msg.tickCounter);

    break;
  }
  }
}
