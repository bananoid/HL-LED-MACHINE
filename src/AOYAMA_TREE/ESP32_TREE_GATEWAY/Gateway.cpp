#include "Gateway.h"
#include "AOYAMA_TREE/COMMON/Messages.h"
#include <WiFi.h>

Gateway *GatewaySingleton = new Gateway();

void Gateway::begin(int wifiChannel, ESPSortedBroadcast::PeerRecord *peerList, int nPeers, Scheduler *runner)
{
  // Peer
  ESPSortedBroadcast::Peer::begin(wifiChannel, peerList, nPeers);

#ifndef OLEDSCREEN_DISABLED
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
#endif

  // // Peer
  // ping.set(TASK_SECOND, TASK_FOREVER, [this]() {
  //   BaseMessage msg;
  //   msg.sourceId = peerDescription.id;
  //   msg.targetId = 2; //random(0, this->nPeers);
  //   broadcastData((uint8_t *)&msg, sizeof(BaseMessage));
  //   screen->println("S:" + String(msg.sourceId) + "->" + String(msg.targetId) + "[PING] " + random(3, 87), 4);
  //   Serial.println("S:" + String(msg.sourceId) + "->" + String(msg.targetId) + "[PING]");
  // });
  // runner->addTask(ping);
  // ping.enable();

  // Serial messenger
  Serial.begin(BAUD_RATE);
  Serial2.begin(BAUD_RATE);

  SerialMessengerSingleton->delegate = this;
  SerialMessengerSingleton->begin(&Serial2, BAUD_RATE);

  // serialUpdateTask.set(10 * TASK_MILLISECOND, TASK_FOREVER, [this]() {
  //   SerialMessengerSingleton->update();
  // });
  // runner->addTask(ping);
  // serialUpdateTask.enable();
}

// when receive WIFI send Serial
void Gateway::receiveDataCB(const uint8_t *mac, const uint8_t *incomingData, int len)
{
  uint8_t type = getMessageTypeFromData(incomingData);
  SerialMessengerSingleton->sendData(incomingData, len);
  // Serial.println("WiFi -> Serial [" + String(type) + ":" + sizeof(incomingData) + "]" + String(random(0, 9)));
#ifndef OLEDSCREEN_DISABLED
  screen->println("WiFi -> Serial [" + String(type) + ":" + sizeof(incomingData) + "]" + String(random(0, 9)), 6);
#endif
}

// When receive Serial send WIFI
void Gateway::serialMessengerReceiveData(const uint8_t *incomingData, int len)
{
  uint8_t type = getMessageTypeFromData(incomingData);
#ifndef OLEDSCREEN_DISABLED
  screen->println("Serial -> Wifi [" + String(type) + "]" + String(random(0, 99)), 7);
#endif
  broadcastData(incomingData, len); // send received data to wifi
}

void Gateway::registerReceiveDataCB()
{
  esp_now_register_recv_cb([](const uint8_t *macaddr, const uint8_t *incomingData, int len) {
    GatewaySingleton->receiveDataCB(macaddr, incomingData, len);
  });
}

// void Gateway::serialMessengerReceiveMsg(BaseMessage *message)
// {
// }

void Gateway::update()
{
  SerialMessengerSingleton->update();
}
