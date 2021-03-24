#include "Gateway.h"
#include "AOYAMA_TREE/COMMON/Messages.h"

Gateway *GatewaySingleton = new Gateway();

void Gateway::begin(int wifiChannel, Scheduler *runner)
{
  ESPSortedBroadcast::Peer::begin(wifiChannel);
  screen = new OledScreen();
  screen->begin();

  ping.set(TASK_SECOND, TASK_FOREVER, [this]() {
    BaseMessage msg;
    msg.sourceId = boardInfo.boardId;
    msg.targetId = 1;
    broadcastData((uint8_t *)&msg, sizeof(BaseMessage));
    screen->print("S:" + String(msg.sourceId) + "->" + String(msg.targetId) + "[PING] " + random(3, 87), 4);
    Serial.println("S:" + String(msg.sourceId) + "->" + String(msg.targetId) + "[PING]");
  });
  runner->addTask(ping);
  ping.enable();
}

void Gateway::receiveDataCB(const uint8_t *mac, const uint8_t *incomingData, int len)
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
  default:
    targetId = -1;
    sourceId = -1;
    messageTypeName = "UNKNOWN";
    break;
  }
  Serial.println("Receiving:" + String(sourceId) + "->" + String(targetId) + "[" + messageTypeName + "]");
  screen->print("R:" + String(sourceId) + "<-" + String(targetId) + "[" + messageTypeName + "] " + random(0, 99), 3);

  // filter
  if (targetId != boardInfo.boardId)
  {
    // pass
  }
  if (targetId == 0)
  {
    // broadcasted message
  }
}

void Gateway::registerReceiveDataCB()
{
  Serial.println("Register Gateway receive callback");
  esp_now_register_recv_cb([](const uint8_t *macaddr, const uint8_t *incomingData, int len) {
    GatewaySingleton->receiveDataCB(macaddr, incomingData, len);
  });
}