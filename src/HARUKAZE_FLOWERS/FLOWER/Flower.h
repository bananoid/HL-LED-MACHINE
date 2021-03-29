#pragma once
#include <Peer.h>

#include "HARUKAZE_FLOWERS/COMMON/config.h"
#include "HARUKAZE_FLOWERS/COMMON/Messages.h"

#define _TASK_STD_FUNCTION
#include <TaskSchedulerDeclarations.h>

#include <FastLED.h>
#include <FastLEDRenderer.h>
#include <LEDSynth.h>
// #include <GFXUtils.h>

#include <WiFi.h>

#define OLEDSCREEN_DISABLED

#ifndef OLEDSCREEN_DISABLED
#include <OledScreen.h>
#endif

#define PIN_LED_RING_TOP 18
#define PIN_LED_RING_BOTTOM 19

#define N_LAYERS 2

class Flower : public ESPSortedBroadcast::Peer
{
private:
public:
  // wifi
  void receiveDataCB(const uint8_t *mac, const uint8_t *incomingData, int len) override;

  void registerReceiveDataCB() override;

  void begin(int wifiChannel, ESPSortedBroadcast::PeerRecord *peerList, int nPeers, Scheduler *runner);

#ifndef OLEDSCREEN_DISABLED
  OledScreen *screen;
  Task displayScreen;
#endif

  Task ping;

  CRGB *leds;

  LEDSynth::FastLEDRenderer ledRenderer;
  LEDSynth::LEDSynth *ledSynth;

  LEDSynth::LEDShaderSynth *shaders[N_LAYERS];
  LEDSynth::LEDShaderSynth *getLayerShader(int n);

  float positionStartOffset = 0;
};

extern Flower *FlowerSingleton;