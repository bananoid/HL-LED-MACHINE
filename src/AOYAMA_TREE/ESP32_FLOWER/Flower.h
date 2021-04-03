#pragma once
#include <Peer.h>

#include "AOYAMA_TREE/COMMON/config.h"
#include "AOYAMA_TREE/COMMON/Messages.h"
#include <BaseMessages.h>
#define _TASK_STD_FUNCTION
#include <TaskSchedulerDeclarations.h>

#include <FastLEDRenderer.h>
#include <LEDSynth.h>
#include <GFXUtils.h>

#include "IMUSensor.h"
#include "TouchSensor.h"
#include "AOYAMA_TREE/COMMON/FlowerState.h"

#include <Tracker.h>
using namespace HLMusicMachine;

// #include "AOYAMA_TREE/COMMON/FlowerState.h"

#define OLEDSCREEN_DISABLED

#ifndef OLEDSCREEN_DISABLED
#include <OledScreen.h>
#endif

class Flower : public ESPSortedBroadcast::Peer, public IMUSensorDelegate, public TouchSensorDelegate
{
private:
public:
  // wifi

  void registerReceiveDataCB() override;
  virtual void receiveFilteredDataCB(uint8_t type,
                                     uint8_t sourceId,
                                     uint8_t targetId,
                                     const uint8_t *mac,
                                     const uint8_t *incomingData,
                                     int len) override;

  void begin(int wifiChannel, ESPSortedBroadcast::PeerRecord *peerList, int nPeers, Scheduler *runner);

#ifndef OLEDSCREEN_DISABLED
  OledScreen *screen;
  Task displayScreen;
#endif

  Task ping;
  Task readIMU;

  uint8_t branchPeerId;

  FlowerStates state;

  LEDSynth::FastLEDRenderer ringLEDRenderer;
  LEDSynth::FastLEDRenderer ballDotLEDRenderer;

  LEDSynth::LEDSynth *ringLEDSynth;
  LEDSynth::LEDSynth *ballDotLEDSynth;

  LEDSynth::LEDShaderSynth *layerALEDShaderSynth;
  LEDSynth::LEDShaderSynth *layerBLEDShaderSynth;

  LEDSynth::LEDShaderSynth *ballDotLEDShaderSynth;

  // void frameRender();

  IMUSensor *imu;
  void onIMUOrientationData(sensors_event_t *orientationData) override;

  TouchSensor *touchSensor;
  Task touchSensorUpdateTask;
  void touchSensorOnTouch(int touchId) override;

  Tracker *tracker;
  void flowerStateChanged(FlowerStates state);

  float activation = 0; // 0 - 1
  float activationIncrease = 0.0007;
  float activationDecay = 0.0005;

  void updateActivation();

  Task activationUpdateTask;

  void update();

  void setSilentRingAnimation();
  void setCallingRingAnimation();
  void setActiveRingAnimation();
};

extern Flower *FlowerSingleton;