#pragma once
#include <Arduino.h>
#include <Track.h>
#include "TrackerFactory.h"
#include "AOYAMA_TREE/COMMON/Messages.h"

#define COUNTDOWN_SILENT_TO_CALING 16
#define COUNTDOWN_CALLING_TO_SILENT 8
#define COUNTDOWN_ACTIVE_TO_SILENT 8

#define THRESHOLD_ACTIVATION 0.03
#define THRESHOLD_EXPLOSION 1.0

#define ACTIVATION_INCREASE 0.0007
#define ACTIVATION_DECAY 0.0005

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
  virtual void flowerActivationParametersChanged(FlowerState *flowerState, float activationIncrease, float activationDecay);
  virtual void flowerExplode();
  virtual void flowerStateSyncTrack(FlowerState *flowerState);
};

class FlowerState
{
public:
  FlowerStateDelegate *delegate = nullptr;
  uint8_t peerId;
  uint8_t branchPeerId;
  FlowerStates state = SILENT;

  HLMusicMachine::Track *track;

  int countdownSilentToCalling = COUNTDOWN_SILENT_TO_CALING;
  int countdownCallingToSilent = COUNTDOWN_CALLING_TO_SILENT;
  int countdownActiveToSilent = COUNTDOWN_ACTIVE_TO_SILENT;

  int callingCountDown = 4; // this decreases to go to call
  int silentCountDown = 4;  // this deacreases to go to silent from calling

  void changeState(FlowerStates state);
  void changeActivationParameters(float activationIncrease, float activationDecay);

  unsigned long timer;

  float thresholdActivation = THRESHOLD_ACTIVATION; // activation threshold from Active to silent
  float thresholdExplosion = THRESHOLD_EXPLOSION;   // activation threshold from Active to silent

  float activation = 0; // 0 - 1
  float activationIncrease = ACTIVATION_INCREASE;
  float activationDecay = ACTIVATION_DECAY;

  static FlowerState *getFlowerStateByPeerId(uint8_t peerId, FlowerState **list, int size);

  void updateWithBar();
  void updateWithFrame();
};
