#pragma once
#include <Peer.h>

#include "AOYAMA_TREE/COMMON/config.h"
#include <BaseMessages.h>
#define _TASK_STD_FUNCTION
#include <TaskSchedulerDeclarations.h>

#include <FastLEDRenderer.h>
#include <LEDSynth.h>
#include <GFXUtils.h>

#include "IMUSensor.h"

#include <OledScreen.h>

class Flower : public ESPSortedBroadcast::Peer, public IMUSensorDelegate
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
  Task readIMU;

  // LEDStrips::FastLEDRenderer topRingLEDRenderer;
  // LEDStrips::FastLEDRenderer bottomRingLEDRenderer;
  // LEDStrips::FastLEDRenderer ballDotLEDRenderer;

  // LEDSynth::LEDSynth *topRingLEDSynth;
  // LEDSynth::LEDSynth *bottomRingLEDSynth;
  // LEDSynth::LEDSynth *ballDotLEDSynth;

  // void frameRender();

  IMUSensor *imu;
  void onIMUOrientationData(sensors_event_t *orientationData) override;
};

extern Flower *FlowerSingleton;