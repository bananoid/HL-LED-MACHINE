#pragma once
#include <Peer.h>

#include "AOYAMA_TREE/COMMON/config.h"
#include <TaskSchedulerDeclarations.h>

#include <Arduino.h>
#include <FastLEDRenderer.h>
#include <LEDSynth.h>
#include <GFXUtils.h>

class Flower : public ESPSortedBroadcast::Peer
{
private:
public:
  void receiveDataCB(const uint8_t *mac, const uint8_t *incomingData, int len) override;

  void registerReceiveDataCB() override;

  void begin(int wifiChannel, Scheduler *runner);

  LEDStrips::FastLEDRenderer topRingLEDRenderer;
  LEDStrips::FastLEDRenderer bottomRingLEDRenderer;
  LEDStrips::FastLEDRenderer ballDotLEDRenderer;

  LEDSynth::LEDSynth *topRingLEDSynth;
  LEDSynth::LEDSynth *bottomRingLEDSynth;
  LEDSynth::LEDSynth *ballDotLEDSynth;

  void frameRender();
};

extern Flower *FlowerSingleton;