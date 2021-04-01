#include "FlowerState.h"

void FlowerState::decreaseSilentCountDown()
{
  silentCountDown--;
  if (silentCountDown == 0)
  {
    state = SILENT;
    delegate->flowerStateChanged(this, state);
  }
}

void FlowerState::decreaseCallingCountDown()
{
  callingCountDown--;
  if (callingCountDown == 0)
  {
    state = CALLING;
    delegate->flowerStateChanged(this, state);
  }
}

void FlowerState::increaseActivation()
{
  activation += activationIncrease;
  activation = min(activation, 1.0f);
}

void FlowerState::updateActivation()
{
  activation -= activationDecay;
  activation = max(activation, 0.0f);

  // if (activation > activationThreshold)
  // {
  //   Serial.println("Flower Active");
  // }
}