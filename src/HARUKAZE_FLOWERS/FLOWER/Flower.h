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

#include <OledScreen.h>

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

  OledScreen *screen;

  Task displayScreen;
  Task ping;

  CRGB *leds;

  LEDSynth::FastLEDRenderer ledRenderer;
  LEDSynth::LEDSynth *ledSynth;

  LEDSynth::LEDShaderSynth *shaders[N_LAYERS];
};

extern Flower *FlowerSingleton;