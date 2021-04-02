#pragma once //to prevent reimport (singleton)

#include <Arduino.h>

#include "config.h"
#include <TaskSchedulerDeclarations.h>

#include <Tracker.h>
#include <Bounce2.h>

#include "AOYAMA_TREE/COMMON/config.h"
#include "AOYAMA_TREE/COMMON/FlowerState.h"

#include <SerialMessenger.h>

using namespace HLSerialMessanger;

class MusicMachine : SerialMessengerDelegate, public HLMusicMachine::TrackerDelegate, public FlowerStateDelegate
{
private:
  /* data */
public:
  MusicMachine(Scheduler *runner);
  Scheduler *runner;

  void begin();
  void update();
  void serialMessengerReceiveData(const uint8_t *incomingData, int len) override;

  Bounce2::Button startStopButton = Bounce2::Button();

  Task updateFrameTask;

  HLMusicMachine::Tracker *tracker;

  FlowerState *flowerStates[NUMBER_OF_FLOWERS];
  void initFlowerStates();

  void trackerBarTick() override;

  void flowerStateChanged(FlowerState *flowerState, FlowerStates state) override;
  void flowerExplode() override;
};