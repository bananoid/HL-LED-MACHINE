#include "Flower.h"
#include "AOYAMA_TREE/COMMON/Messages.h"
#include "FastLED.h"

Flower *FlowerSingleton = new Flower();

void Flower::begin(int wifiChannel, Scheduler *runner)
{
  ESPSortedBroadcast::Peer::begin(wifiChannel);

  CRGB *leds;

  leds = new CRGB[24];
  FastLED.addLeds<WS2812B, 18, GRB>(leds, 24); // top
  topRingLEDRenderer.begin(leds, 24);
  topRingLEDSynth = new LEDSynth::LEDSynth(24, &topRingLEDRenderer, runner);

  leds = new CRGB[24];
  FastLED.addLeds<WS2812B, 5, GRB>(leds, 24); // bottom
  bottomRingLEDRenderer.begin(leds, 24);
  bottomRingLEDSynth = new LEDSynth::LEDSynth(24, &bottomRingLEDRenderer, runner);

  leds = new CRGB[1];
  FastLED.addLeds<WS2812B, 19, GRB>(leds, 1); // dot
  ballDotLEDRenderer.begin(leds, 1);
  ballDotLEDSynth = new LEDSynth::LEDSynth(1, &ballDotLEDRenderer, runner);
}

void Flower::receiveDataCB(const uint8_t *mac, const uint8_t *incomingData, int len)
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

void Flower::registerReceiveDataCB()
{
  Serial.println("Register Flower receive callback");
  esp_now_register_recv_cb([](const uint8_t *macaddr, const uint8_t *incomingData, int len) {
    FlowerSingleton->receiveDataCB(macaddr, incomingData, len);
  });
}
