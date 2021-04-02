#include "Branch.h"

Branch *BranchSingleton = new Branch();

void Branch::begin(int wifiChannel, ESPSortedBroadcast::PeerRecord *peerList, int nPeers, Scheduler *runner)
{
  ESPSortedBroadcast::Peer::begin(wifiChannel, peerList, nPeers);
  enableFilter = false;

  flowerPeerId = peerDescription.id - NUMBER_OF_FLOWERS;

  tracker = new Tracker(runner);

  const uint8_t pins[3] = {32, 33, 25};
  PolyPinInstrumet *instrument = new PolyPinInstrumet(runner, pins, 3);
  track = TrackerFactory::buildTrackWithInstrument(tracker, instrument); // TODO: Make PolyPin instriment 32 33 25
  tracker->clock->play();
  // track->play();

  flowerStateChanged(FlowerStates::SILENT);
}

void Branch::registerReceiveDataCB()
{
  esp_now_register_recv_cb([](const uint8_t *macaddr, const uint8_t *incomingData, int len) {
    BranchSingleton->receiveDataCB(macaddr, incomingData, len);
  });
}

void Branch::receiveFilteredDataCB(uint8_t messageType, uint8_t sourceId, uint8_t targetId, const uint8_t *mac, const uint8_t *incomingData, int len)
{

  // if (targetId != 0 && targetId != flowerPeerId && targetId != peerDescription.id || sourceId != flowerPeerId)
  // {
  //   return;
  // }

  switch (messageType)
  {

  case CLOCK_SYNC:
  {
    ClockSyncMessage msg;
    memcpy(&msg, incomingData, sizeof(ClockSyncMessage));
    // Serial.printf("CLOCK_SYNC %i %f\n ", msg.tickCounter, msg.bpm);
    tracker->clock->syncTo(msg.tickCounter, msg.bpm);
    break;
  }
  case FLOWER_SYNC_TRACK:
  {
    FlowerSyncTrackMessage msg;
    memcpy(&msg, incomingData, sizeof(FlowerSyncTrackMessage));
    TrackerFactory::setSequncerParametersForTrack(track, msg.sequencerA, msg.sequencerB);

    // Serial.printf("FLOWER_CALL seed:%i type:%i nseq:%i\n", msg.seed, msg.trackType, track->sequencers.size());

    break;
  }
  case FLOWER_STATE:
  {
    FlowerStateMessage msg;
    memcpy(&msg, incomingData, sizeof(FlowerStateMessage));
    if (msg.targetId == flowerPeerId)
    {
      Serial.printf("receive message from [%i] state [%i]\n", flowerPeerId, msg.state);
      flowerStateChanged((FlowerStates)msg.state);
    }
    break;
  }
  case FLOWER_ACTIVATION:
  {
    FlowerActivationMessage msg;
    memcpy(&msg, incomingData, sizeof(FlowerActivationMessage));
    if (msg.sourceId == flowerPeerId)
    {
      activation = msg.activation;
      onActivationChanged();
    }
    break;
  }
  }
}

void Branch::flowerStateChanged(FlowerStates state)
{
  Serial.printf("Flower State Changed %i\n", state);

  this->state = state;

  switch (state)
  {
  case FlowerStates::SILENT:
  {
    Serial.println("Change State to SILENT");
    activation = 0;
    track->stop();
    // track->play();
    break;
  }
  case FlowerStates::CALLING:
  {
    Serial.println("Change State to CALLING");
    break;
  }
  case FlowerStates::ACTIVE:
  {
    Serial.println("Change State to ACTIVE");
    track->play();
    break;
  }
  }
}

void Branch::onActivationChanged()
{
  float fillFactor = activation; //Todo map from minThreshold and maxThreshold
  Serial.printf("activation %f\n", fillFactor);
  // // track->setFillFactor(fillFactor);

  // track->setFillFactor(fillFactor);
  track->setFillFactor(1);
}

void Branch::update()
{
  // Serial.printf("peer id %i, flower id %i\n", peerDescription.id, flowerPeerId);
  // if (state == FlowerStates::ACTIVE)
  // {
  //   Serial.printf("activation: [%f]\n", activation);
  // }
}
