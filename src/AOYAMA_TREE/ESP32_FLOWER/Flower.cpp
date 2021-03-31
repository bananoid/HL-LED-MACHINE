#include "Flower.h"
#include "AOYAMA_TREE/COMMON/Messages.h"
#include <WiFi.h>
#include "FastLED.h"

Flower *FlowerSingleton = new Flower();

void Flower::begin(int wifiChannel, ESPSortedBroadcast::PeerRecord *peerList, int nPeers, Scheduler *runner)
{
  // Peer
  ESPSortedBroadcast::Peer::begin(wifiChannel, peerList, nPeers);

  // Screen
  screen = new OledScreen(8, 22);
  screen->begin();
  screen->println(FlowerSingleton->peerDescription.name, 0);
  screen->println(WiFi.macAddress(), 1);
  screen->displayScreen();
  displayScreen.set(50 * TASK_MILLISECOND, TASK_FOREVER, [this]() {
    screen->sayHello(2);
    screen->displayScreen();
  });
  runner->addTask(displayScreen);
  displayScreen.enable();

  // // led
  // CRGB *leds;

  // leds = new CRGB[24];
  // FastLED.addLeds<WS2812B, 18, GRB>(leds, 24); // top
  // topRingLEDRenderer.begin(leds, 24);
  // topRingLEDSynth = new LEDSynth::LEDSynth(24, &topRingLEDRenderer, runner);

  // leds = new CRGB[24];
  // FastLED.addLeds<WS2812B, 5, GRB>(leds, 24); // bottom
  // bottomRingLEDRenderer.begin(leds, 24);
  // bottomRingLEDSynth = new LEDSynth::LEDSynth(24, &bottomRingLEDRenderer, runner);

  // leds = new CRGB[1];
  // FastLED.addLeds<WS2812B, 19, GRB>(leds, 1); // dot
  // ballDotLEDRenderer.begin(leds, 1);
  // ballDotLEDSynth = new LEDSynth::LEDSynth(1, &ballDotLEDRenderer, runner);

  // IMU
  // imu = new IMUSensor(this);
  // imu->begin();

  // readIMU.set(10 * TASK_MILLISECOND, TASK_FOREVER, [this]() {
  //   // Serial.println("reading IMU");
  //   // imu->update();
  // });
  // runner->addTask(readIMU);
  // readIMU.enable();

  // // Peer
  // ping.set(TASK_SECOND, TASK_FOREVER, [this]() {
  //   BaseMessage msg;
  //   msg.sourceId = peerDescription.id;
  //   msg.targetId = random(0, this->nPeers);
  //   broadcastData((uint8_t *)&msg, sizeof(BaseMessage));
  //   screen->println("S:" + String(msg.sourceId) + "->" + String(msg.targetId) + "[PING] " + random(3, 87), 4);
  //   Serial.println("S:" + String(msg.sourceId) + "->" + String(msg.targetId) + "[PING]");
  // });
  // runner->addTask(ping);
  // ping.enable();
}

void Flower::onIMUOrientationData(sensors_event_t *orientationData)
{
  double x, y, z;
  x = orientationData->orientation.x;
  y = orientationData->orientation.y;
  z = orientationData->orientation.z;
}

void Flower::receiveDataCB(const uint8_t *mac, const uint8_t *incomingData, int len)
{
  uint8_t messageType = getMessageTypeFromData(incomingData);

  switch (messageType)
  {

  case PING:
  {
    BaseMessage pingMessage;
    memcpy(&pingMessage, incomingData, sizeof(pingMessage));
    break;
  }
  case TREE_STATE:
  {
    TreeStateMessage msg;
    memcpy(&msg, incomingData, sizeof(TreeStateMessage));
    Serial.printf("events %f %f", msg.parameters.velocityLFO, msg.parameters.retrigLFO);
    screen->println("e " + String(msg.parameters.velocityLFO) + " v" + String(msg.parameters.retrigLFO), 4);

    broadcastData(incomingData, len);
    break;
  }
  default:
    break;
  }
}

void Flower::registerReceiveDataCB()
{
  esp_now_register_recv_cb([](const uint8_t *macaddr, const uint8_t *incomingData, int len) {
    FlowerSingleton->receiveDataCB(macaddr, incomingData, len);
  });
}
