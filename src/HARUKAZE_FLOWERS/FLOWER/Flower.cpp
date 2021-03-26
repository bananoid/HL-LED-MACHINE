#include "Flower.h"

// #include <LEDShader.h>
// #include <LEDShaderSynth.h>
// #include <LEDShaderDiffusion.h>

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
  Serial.println(WiFi.macAddress());
  displayScreen.set(50 * TASK_MILLISECOND, TASK_FOREVER, [this]() {
    screen->displayScreen();
  });
  runner->addTask(displayScreen);
  displayScreen.enable();

  // Ping
  // ping.set(TASK_SECOND, TASK_FOREVER, [this]() {
  //   BaseMessage msg;
  //   msg.sourceId = peerDescription.id;
  //   msg.targetId = 1; //random(0, this->nPeers);
  //   broadcastData((uint8_t *)&msg, sizeof(BaseMessage));
  //   screen->println("S:" + String(msg.sourceId) + "->" + String(msg.targetId) + "[PING] " + random(3, 87), 4);
  //   Serial.println("S:" + String(msg.sourceId) + "->" + String(msg.targetId) + "[PING]");
  // });
  // runner->addTask(ping);
  // ping.enable();

  // LEDs
  // CRGB *leds;
  int numOffLeds = 24;

  leds = new CRGB[numOffLeds];
  FastLED.addLeds<WS2812B, PIN_LED_RING_TOP, GRB>(leds, numOffLeds);
  FastLED.addLeds<WS2812B, PIN_LED_RING_BOTTOM, GRB>(leds, numOffLeds);

  // for (int i = 0; i < numOffLeds; i++)
  // {
  //   /* code */
  //   leds[i] = CRGB::Blue;
  // }
  // FastLED.show();
  ledRenderer.begin(leds, numOffLeds);
  ledSynth = new LEDSynth::LEDSynth(numOffLeds, &ledRenderer, runner);

  // LEDSynth::LEDShaderSynth *shader;

  for (int i = 0; i < N_LAYERS; i++)
  {
    shaders[i] = ledSynth->addLEDShaderSynth();
    // shader->targetState->speed = 0.13;
    // shader->targetState->hue = 0.5;
    // shader->targetState->hueRad = 0;
    // shader->targetState->scale = 0.1;
    // shader->targetState->que = 2.;
  }
}

void Flower::receiveDataCB(const uint8_t *mac, const uint8_t *incomingData, int len)
{
  // Serial.println("Receiving Message!");
  String messageTypeName;

  uint8_t messageType = getMessageTypeFromData(incomingData);
  uint targetId;
  uint sourceId;

  // uint8_t action;
  // memcpy(&action, incomingData, sizeof(uint8_t));
  // Serial.println(String(action));

  // AudioBandsMessage msg;
  // memcpy(&msg, incomingData, sizeof(msg));
  // screen->println(String(sizeof(msg)), 6);
  // targetId = msg.targetId;
  // sourceId = msg.sourceId;
  // messageTypeName = "Audio Bands";
  // char c[22];
  // // sprintf(c, "L:%3d M:%3d H:%3d", int(msg.bandLowVal * 999), int(msg.bandMidVal * 999), int(msg.bandHighVal * 999));
  // screen->println(c, 7);

  // BaseMessage pingMessage;
  // memcpy(&pingMessage, incomingData, sizeof(pingMessage));
  // Serial.printf(pingMessage.targetId)

  Serial.println(messageType);

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
  case MSG_AUDIO_BANDS:
  {
    AudioBandsMessage msg;
    memcpy(&msg, incomingData, sizeof(msg));
    targetId = msg.targetId;
    sourceId = msg.sourceId;
    messageTypeName = "Audio Bands";
    char c[22];
    sprintf(c, "L:%3d M:%3d H:%3d", int(msg.bandLowVal * 999), int(msg.bandMidVal * 999), int(msg.bandHighVal * 999));
    screen->println(c, 7);
    break;
  }
    // case MSG_LED_SYNTH_LAYER:
    // {
    //   LedSynthLayerMessage msg;
    //   memcpy(&msg, incomingData, sizeof(msg));
    //   targetId = msg.targetId;
    //   sourceId = msg.sourceId;
    //   messageTypeName = "Led Layer Msg";
    //   screen->println("Receiving layer:" + String(msg.layer) + " " + String(random(9)), 6);
    //   break;
    // }

  case MSG_LED_SYNTH_LAYER_COLOR:
  {
    LedSynthLayerColorMessage msg;
    memcpy(&msg, incomingData, sizeof(msg));
    uint8_t layer = msg.layer;
    LEDSynth::LEDShaderSynth *shader = shaders[layer];
    shader->targetState->hue = msg.hue;
    shader->targetState->hueRad = msg.hueRad;
    shader->targetState->scale = msg.scale;
    shader->targetState->speed = msg.speed * 0.01;
    shader->targetState->intensity = msg.intensity;
    Serial.println("test");
    screen->println("Receiving layer:" + String(msg.layer) + " " + String(msg.intensity), 6);

    break;
  }

  case MSG_LED_SYNTH_LAYER_SHAPE:
  {
    LedSynthLayerShapeMessage msg;
    memcpy(&msg, incomingData, sizeof(msg));
    uint8_t layer = msg.layer;
    LEDSynth::LEDShaderSynth *shader = shaders[layer];
    shader->targetState->que = msg.que;
    shader->targetState->sym = msg.sym;
    shader->targetState->fmAmo = msg.fmAmo;
    shader->targetState->fmFrq = msg.fmFrq;
    break;
  }

  case MSG_LED_SYNTH_GLOBAL:
  {
    LedSynthGlobalMessage msg;
    memcpy(&msg, incomingData, sizeof(msg));
    targetId = msg.targetId;
    sourceId = msg.sourceId;
    messageTypeName = "Led Global Msg";
    if (targetId == peerDescription.id || targetId == 0)
    {
      screen->println("R intensity: " + String(msg.globalIntensity), 6);
    }
    break;
  }
  default:
    targetId = -1;
    sourceId = -1;
    messageTypeName = "UNKNOWN";
    break;
  }

  // // filter
  // if (targetId == peerDescription.id)
  // {
  //   Serial.println("Receiving:" + String(targetId) + "<-" + String(sourceId) + "[" + messageTypeName + "]");
  //   screen->println("R{O}:" + String(targetId) + "<-" + String(sourceId) + "[" + messageTypeName + "] " + random(0, 99), 3);
  // }
  // else if (targetId == 0)
  // {
  //   // broadcasted message
  //   Serial.println("Receiving:" + String(targetId) + "<-" + String(sourceId) + "[" + messageTypeName + "]");
  //   screen->println("R{B}:" + String(targetId) + "<-" + String(sourceId) + "[" + messageTypeName + "] " + random(0, 99), 3);
  // }
  // else
  // {
  //   // // broadcasted message
  //   // Serial.println("Receiving:" + String(targetId) + "<-" + String(sourceId) + "[" + messageTypeName + "]");
  //   // screen->println("R{X}:" + String(targetId) + "<-" + String(sourceId) + "[" + messageTypeName + "] " + random(0, 99), 3);
  // }
}

void Flower::registerReceiveDataCB()
{
  esp_now_register_recv_cb([](const uint8_t *macaddr, const uint8_t *incomingData, int len) {
    FlowerSingleton->receiveDataCB(macaddr, incomingData, len);
  });
}
