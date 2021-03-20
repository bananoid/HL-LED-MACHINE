#pragma once
#include <Peer.h>

#include "AOYAMA_TREE/COMMON/config.h"
#include <TaskSchedulerDeclarations.h>

#include <Arduino.h>
#include <FastLEDRenderer.h>
#include <LEDSynth.h>
#include <GFXUtils.h>

#include "IMUSensor.h"

class Flower : public ESPSortedBroadcast::Peer, public IMUSensorDelegate
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

  IMUSensor *imu;
  void onIMUOrientationData(sensors_event_t *orientationData) override;
};

extern Flower *FlowerSingleton;