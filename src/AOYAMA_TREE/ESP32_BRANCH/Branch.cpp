#include "Branch.h"
#include "AOYAMA_TREE/COMMON/Messages.h"

Branch *BranchSingleton = new Branch();

void Branch::begin(int wifiChannel, Scheduler *runner)
{
  ESPSortedBroadcast::Peer::begin(wifiChannel);

  tracker = new Tracker(runner);

  Sequencer *sequencer;

  //////////////////////////
  sequencer = new Sequencer(tracker, new PinIntrument(32, runner)); //ok
  tracker->appendTrack(sequencer);
  sequencer->stepLenght = 6;
  // track->retrig = -1;
  sequencer->retrigLFO = 13;
  sequencer->generator->steps = 16;
  sequencer->generator->events = 8;
  sequencer->generator->offset = 0;
  sequencer->velocity = 127;
  // track->velocityLFO = 2;

  //////////////////////////
  sequencer = new Sequencer(tracker, new PinIntrument(25, runner));
  tracker->appendTrack(sequencer);
  sequencer->stepLenght = 6;
  // track->retrig = -1;
  sequencer->retrigLFO = 6;
  sequencer->generator->steps = 16;
  sequencer->generator->events = 8;
  sequencer->generator->offset = 0;
  sequencer->velocity = 127;
  // track->velocityLFO = 2;

  //////////////////////////
  sequencer = new Sequencer(tracker, new PinIntrument(26, runner));
  tracker->appendTrack(sequencer);
  sequencer->stepLenght = 6;
  // track->retrig = -1;
  sequencer->retrigLFO = 96;
  sequencer->generator->steps = 16;
  sequencer->generator->events = 8;
  sequencer->generator->offset = 0;
  sequencer->velocity = 127;
  // track->velocityLFO = 2;

  //////////////////////////
  sequencer = new Sequencer(tracker, new PinIntrument(33, runner)); //ok
  tracker->appendTrack(sequencer);
  sequencer->stepLenght = 6;
  // track->retrig = -1;
  sequencer->retrigLFO = 38;
  sequencer->generator->steps = 16;
  sequencer->generator->events = 8;
  sequencer->generator->offset = 0;
  sequencer->velocity = 127;
  // track->velocityLFO = 2;
}

void Branch::receiveDataCB(const uint8_t *mac, const uint8_t *incomingData, int len)
{
  uint8_t messageType = getMessageTypeFromData(incomingData);
  uint targetId;
  uint sourceId;

  // Serial.println("Receiving Message!");
  String messageTypeName;

  switch (messageType)
  {

  case PING:
  {
    BaseMessage pingMessage;
    memcpy(&pingMessage, incomingData, sizeof(pingMessage));
    targetId = pingMessage.targetId;
    sourceId = pingMessage.sourceId;
    messageTypeName = "ping";
    break;
  }
  case FLOWER_TOUCH:
  {
    FlowerTouchMessage flowerTouchMessage;
    memcpy(&flowerTouchMessage, incomingData, sizeof(flowerTouchMessage));
    targetId = flowerTouchMessage.targetId;
    sourceId = flowerTouchMessage.sourceId;
    messageTypeName = "flower touch";
    break;
  }
  case FLOWER_LED:
  {
    FlowerLedMessage flowerLedMessage;
    memcpy(&flowerLedMessage, incomingData, sizeof(flowerLedMessage));
    targetId = flowerLedMessage.targetId;
    sourceId = flowerLedMessage.sourceId;
    messageTypeName = "flower LED";
    break;
  }
  case BRANCH_STATE:
  {
    BranchStateMessage branchStateMessage;
    memcpy(&branchStateMessage, incomingData, sizeof(branchStateMessage));
    targetId = branchStateMessage.targetId;
    sourceId = branchStateMessage.sourceId;
    messageTypeName = "branch state";
    break;
  }
  default:
    targetId = -1;
    sourceId = -1;
    messageTypeName = "UNKNOWN";
    break;
  }
  Serial.println("Receiving:" + String(sourceId) + "->" + String(targetId) + "[" + messageTypeName + "]");
}

void Branch::registerReceiveDataCB()
{
  Serial.println("Register Branch receive callback");
  esp_now_register_recv_cb([](const uint8_t *macaddr, const uint8_t *incomingData, int len) {
    BranchSingleton->receiveDataCB(macaddr, incomingData, len);
  });
}
