#include "FlowerState.h"

FlowerState *FlowerState::getFlowerStateByPeerId(uint8_t peerId, FlowerState **list, int size)
{
  for (uint8_t i = 0; i < size; i++)
  {
    if (list[i]->peerId == peerId)
    {
      return list[i];
    }
  }
  return nullptr;
}

void FlowerState::changeActivationParameters(float activationIncrease, float activationDecay)
{
  this->activationIncrease = activationIncrease;
  this->activationDecay = activationDecay;
  delegate->flowerActivationParametersChanged(this, activationIncrease, activationDecay);
}

void FlowerState::changeState(FlowerStates state)
{

  this->state = state;
  delegate->flowerStateChanged(this, state);

  switch (state)
  {
  case SILENT:
    countdownSilentToCalling = COUNTDOWN_SILENT_TO_CALING; //random(1, 4);
    // countdownSilentToCalling = COUNTDOWN_SILENT_TO_CALING * random(1, 5);
    track->stop();
    activation = 0;

    // CHANGE animation

    break;

  case CALLING:
    countdownCallingToSilent = COUNTDOWN_CALLING_TO_SILENT; //random(4, 32); // reset silent
    // countdownCallingToSilent = COUNTDOWN_CALLING_TO_SILENT * random(1, 5);

    track->radomize();
    track->play();

    changeActivationParameters(ACTIVATION_INCREASE, ACTIVATION_DECAY);

    delegate->flowerStateSyncTrack(this);

    // Change animation
    break;

  case ACTIVE:
    countdownActiveToSilent = COUNTDOWN_ACTIVE_TO_SILENT;
    changeActivationParameters(ACTIVATION_INCREASE, ACTIVATION_DECAY);
    // change animation
    break;

  default:
    break;
  }
}

void FlowerState::updateWithBar()
{

  switch (state)
  {
  case SILENT:
    // count calling count down
    // flowerState->silentUpdate();

    // if (random(10) > 3) // percentage of reduce countdown to call
    // {
    //   countdownSilentToCalling--;
    // }
    countdownSilentToCalling--;

    // whent count down reach 0 change state to call
    if (countdownSilentToCalling <= 0)
    {
      changeState(CALLING);
    }

    break;
  case CALLING:
    // count downd to go from calling to silent
    // when call down reach 0 chenge state to silent
    // whent count down reach 0 change state to call
    countdownCallingToSilent--;
    if (countdownCallingToSilent <= 0)
    {
      changeState(SILENT);
    }

    // count up to reach active state if condition is met (touch)
    // if counter reaches threshold, go to active

    break;
  case ACTIVE:

    if (activation <= 0)
    {
      changeState(SILENT);
    }

    break;

  default:
    break;
  }
}

void FlowerState::updateWithFrame()
{

  switch (state)
  {
  case SILENT:

    break;
  case CALLING:

    if (activation >= thresholdActivation)
    {
      changeState(ACTIVE);
    }

    break;
  case ACTIVE:

    if (activation >= thresholdExplosion)
    {
      changeState(SILENT);
    }

    break;

  default:
    break;
  }
}