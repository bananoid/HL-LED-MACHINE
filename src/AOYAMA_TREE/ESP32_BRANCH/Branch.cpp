#include "Branch.h"
#include "AOYAMA_TREE/COMMON/Messages.h"

Branch *BranchSingleton = new Branch();

void Branch::begin(int wifiChannel, Scheduler *runner)
{
  ESPSortedBroadcast::Peer::begin(wifiChannel);
  screen = new Screen(runner);
  screen->begin();

  sequencer = new Sequencer(runner);

  Track *track;

  //////////////////////////
  track = new Track(sequencer, new PinIntrument(32, runner));
  sequencer->appendTrack(track);
  track->stepLenght = 48;
  track->retrig = -1;
  track->retrigLFO = 13;
  track->generator->steps = 16;
  track->generator->events = 4;
  track->generator->offset = 0;
  track->velocity = 127;
  // track->velocityLFO = 2;

  //////////////////////////
  track = new Track(sequencer, new PinIntrument(35, runner));
  sequencer->appendTrack(track);
  track->stepLenght = 24;
  track->retrig = -1;
  track->retrigLFO = 6;
  track->generator->steps = 16;
  track->generator->events = 7;
  track->generator->offset = 0;
  track->velocity = 127;
  // track->velocityLFO = 2;

  //////////////////////////
  track = new Track(sequencer, new PinIntrument(34, runner));
  sequencer->appendTrack(track);
  track->stepLenght = 24;
  track->retrig = -1;
  track->retrigLFO = 6;
  track->generator->steps = 16;
  track->generator->events = 7;
  track->generator->offset = 0;
  track->velocity = 127;
  // track->velocityLFO = 2;

  //////////////////////////
  track = new Track(sequencer, new PinIntrument(34, runner));
  sequencer->appendTrack(track);
  track->stepLenght = 24;
  track->retrig = -1;
  track->retrigLFO = 6;
  track->generator->steps = 16;
  track->generator->events = 7;
  track->generator->offset = 0;
  track->velocity = 127;
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
  screen->print(String(sourceId) + "->" + String(targetId) + "[" + messageTypeName + "]", 40);
  // screen->displayScreen();
}

void Branch::registerReceiveDataCB()
{
  Serial.println("Register Branch receive callback");
  esp_now_register_recv_cb([](const uint8_t *macaddr, const uint8_t *incomingData, int len) {
    BranchSingleton->receiveDataCB(macaddr, incomingData, len);
  });
}
