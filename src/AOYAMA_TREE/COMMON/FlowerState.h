#pragma once
#include <Arduino.h>
#include <Track.h>
#include "TrackerFactory.h"
#include "AOYAMA_TREE/COMMON/Messages.h"

enum FlowerStates
{
  SILENT,
  CALLING,
  ACTIVE
};
class FlowerState;
class FlowerStateDelegate
{
public:
  virtual void flowerStateChanged(FlowerState *flowerState, FlowerStates state);
  virtual void flowerExplode();
};

class FlowerState
{
public:
  FlowerStateDelegate *delegate = nullptr;
  uint8_t peerId;
  uint8_t branchPeerId;
  FlowerStates state = SILENT;

  HLMusicMachine::Track *track;

  int countdownSilentToCalling = 4;
  int countdownCallingToSilent = 4;
  int countdownActiveToSilent = 4;

  int callingCountDown = 4; // this decreases to go to call
  int silentCountDown = 4;  // this deacreases to go to silent from calling

  void changeState(FlowerStates state);

  // void decreaseSilentCountDown();
  // void decreaseCallingCountDown();

  unsigned long timer;

  float activationThreshold = 0.2; // activation threshold from Active to silent
  float explosionThreshold = 0.6;  // activation threshold from Active to silent

  float activation = 0; // 0 - 1
  // float activationIncrease = 0.0007;
  // float activationDecay = 0.0005;

  // void increaseActivation();

  // void updateActivation();

  static FlowerState *getFlowerStateByPeerId(uint8_t peerId, FlowerState **list, int size);

  void updateWithBar();
  void updateWithFrame();
  // void updateSilentState();
  // void updateCallingState();
  // void updateActiveState();
};
