#include "Gateway.h"
#include "AOYAMA_TREE/COMMON/Messages.h"
#include <WiFi.h>

Gateway *GatewaySingleton = new Gateway();

void Gateway::begin(int wifiChannel, ESPSortedBroadcast::PeerRecord *peerList, int nPeers, Scheduler *runner)
{
  // Peer
  ESPSortedBroadcast::Peer::begin(wifiChannel, peerList, nPeers);

  // Screen
  screen = new OledScreen(8, 22);
  screen->begin();
  screen->println(GatewaySingleton->peerDescription.name, 0);
  screen->println(WiFi.macAddress(), 1);
  Serial.println(WiFi.macAddress());
  displayScreen.set(50 * TASK_MILLISECOND, TASK_FOREVER, [this]() {
    screen->displayScreen();
  });
  runner->addTask(displayScreen);
  displayScreen.enable();

  // Peer
  ping.set(TASK_SECOND, TASK_FOREVER, [this]() {
    BaseMessage msg;
    msg.sourceId = peerDescription.id;
    msg.targetId = random(0, this->nPeers);
    broadcastData((uint8_t *)&msg, sizeof(BaseMessage));
    screen->println("S:" + String(msg.sourceId) + "->" + String(msg.targetId) + "[PING] " + random(3, 87), 4);
    Serial.println("S:" + String(msg.sourceId) + "->" + String(msg.targetId) + "[PING]");
  });
  runner->addTask(ping);
  ping.enable();

  // Serial messenger
  Serial.begin(BAUD_RATE);
  Serial2.begin(BAUD_RATE);

  SerialMessengerSingleton->delegate = this;
  SerialMessengerSingleton->begin(&Serial2, BAUD_RATE);
}

void Gateway::receiveDataCB(const uint8_t *mac, const uint8_t *incomingData, int len)
{
  SerialMessengerSingleton->sendData(incomingData, len);
  screen->println("Sending Serial" + random(0, 99), 6);

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
  // case ROCK_BPM:
  // {
  //   BaseMessage pingMessage;
  //   memcpy(&pingMessage, incomingData, sizeof(pingMessage));
  //   targetId = pingMessage.targetId;
  //   sourceId = pingMessage.sourceId;
  //   messageTypeName = "ping";
  //   break;
  // }
  default:
    targetId = -1;
    sourceId = -1;
    messageTypeName = "UNKNOWN";
    break;
  }

  // filter
  if (targetId == peerDescription.id)
  {
    Serial.println("Receiving:" + String(sourceId) + "->" + String(targetId) + "[" + messageTypeName + "]");
    screen->println("R:" + String(sourceId) + "<-" + String(targetId) + "[" + messageTypeName + "] " + random(0, 99), 3);
  }
  else if (targetId == 0)
  {
    // broadcasted message
    Serial.println("Receiving:" + String(sourceId) + "->" + String(targetId) + "[" + messageTypeName + "]");
    screen->println("R{B}:" + String(sourceId) + "<-" + String(targetId) + "[" + messageTypeName + "] " + random(0, 99), 3);
  }
  else
  {
    // pass
  }
}

void Gateway::registerReceiveDataCB()
{
  esp_now_register_recv_cb([](const uint8_t *macaddr, const uint8_t *incomingData, int len) {
    GatewaySingleton->receiveDataCB(macaddr, incomingData, len);
  });
}

void Gateway::update()
{
  SerialMessengerSingleton->update();
}

void Gateway::serialMessengerReceiveMsg(BaseMessage *message){

};
void Gateway::serialMessengerReceiveData(const uint8_t *incomingData, int len)
{
  Serial.println("Receive data!");
  broadcastData(incomingData, len); // send received data to wifi
}
