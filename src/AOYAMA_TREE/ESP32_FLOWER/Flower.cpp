#include "Flower.h"
#include "AOYAMA_TREE/COMMON/Messages.h"

Flower *FlowerSingleton = new Flower();

void Flower::begin(int wifiChannel, Scheduler *runner)
{
  ESPSortedBroadcast::Peer::begin(wifiChannel);
  screen = new Screen(runner);
  screen->begin();
}

void Flower::receiveDataCB(const uint8_t *mac, const uint8_t *incomingData, int len)
{
  digitalWrite(2, HIGH);
  delay(500);
  digitalWrite(2, LOW);

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

void Flower::registerReceiveDataCB()
{
  Serial.println("Register Flower receive callback");
  esp_now_register_recv_cb([](const uint8_t *macaddr, const uint8_t *incomingData, int len) {
    FlowerSingleton->receiveDataCB(macaddr, incomingData, len);
  });
}
