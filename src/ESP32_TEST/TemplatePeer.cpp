#include "TemplatePeer.h"

TemplatePeer *TemplatePeerSingleton = new TemplatePeer();

void TemplatePeer::begin(int wifiChannel, Scheduler *runner)
{
  ESPSortedBroadcast::Peer::begin(wifiChannel);
}

void TemplatePeer::receiveDataCB(const uint8_t *mac, const uint8_t *incomingData, int len)
{
  // uint8_t messageType = getMessageTypeFromData(incomingData);
  // uint targetId;
  // uint sourceId;

  // // Serial.println("Receiving Message!");
  // String messageTypeName;

  // switch (messageType)
  // {

  // case PING:
  // {
  //   BaseMessage pingMessage;
  //   memcpy(&pingMessage, incomingData, sizeof(pingMessage));
  //   targetId = pingMessage.targetId;
  //   sourceId = pingMessage.sourceId;
  //   messageTypeName = "ping";
  //   break;
  // }
  // default:
  //   targetId = -1;
  //   sourceId = -1;
  //   messageTypeName = "UNKNOWN";
  //   break;
  // }
  // Serial.println("Receiving:" + String(sourceId) + "->" + String(targetId) + "[" + messageTypeName + "]");
}

void TemplatePeer::registerReceiveDataCB()
{
  Serial.println("Register TemplatePeer receive callback");
  esp_now_register_recv_cb([](const uint8_t *macaddr, const uint8_t *incomingData, int len) {
    TemplatePeerSingleton->receiveDataCB(macaddr, incomingData, len);
  });
}