#pragma once
#include <Arduino.h>
#include <Track.h>

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
};

class FlowerState
{
public:
  FlowerStateDelegate *delegate = nullptr;
  uint8_t peerId;
  FlowerStates state = SILENT;

  uint32_t seed;

  HLMusicMachine::Track *track;

  int callingCountDown = 4;
  int silentCountDown = 4;

  void decreaseSilentCountDown();
  void decreaseCallingCountDown();

  unsigned long timer;

  float activationThreshold = 0.5; // activation threshold from Active to silent
  float activation = 0;            // 0 - 1
  float activationIncrease = 0.007;
  float activationDecay = 0.005;

  void increaseActivation();

  void updateActivation();
};
