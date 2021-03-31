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
  // float threshold = 0.5; // activation threshold from Active to silent
  // float activation = 0;  // 0 - 1

  // float activationDecay = 0.01;
  // float activationIncrease = 0.01;

  int callingCountDown = 4;
  int silentCountDown = 4;

  unsigned long timer;

  // void increaseActivation()
  // {
  //   activation += activationIncrease;
  //   activation = min(activation, 1);
  // }

  void decreaseSilentCountDown();

  void decreaseCallingCountDown();

  // void update()
  // {
  //   activation -= activationDecay;
  //   activation = max(activation, 0);

  //   if (activation > threshold)
  //   {
  //     Serial.println("Flower Active");
  //   }
  // }
};
