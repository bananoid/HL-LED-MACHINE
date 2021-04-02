#include "FlowerState.h"

// void FlowerState::decreaseSilentCountDown()
// {
//   silentCountDown--;
//   if (silentCountDown == 0)
//   {
//     state = SILENT;
//     delegate->flowerStateChanged(this, state);
//   }
// }

// void FlowerState::decreaseCallingCountDown()
// {
//   callingCountDown--;
//   if (callingCountDown == 0)
//   {
//     state = CALLING;
//     delegate->flowerStateChanged(this, state);
//   }
// }

// void FlowerState::increaseActivation()
// {
//   activation += activationIncrease;
//   activation = min(activation, 1.0f);

//   // Serial.printf("increaseActivation %f %i\n", activation, random(99));
// }

// void FlowerState::updateActivation()
// {
//   if (state == SILENT)
//   {
//     return;
//   }

//   // Serial.printf("update activation %f %i\n", activation, random(99));

//   // if (activation <= 0 && state == ACTIVE) // From active to silent by cooldown
//   // {
//   //   state = SILENT;
//   //   activation = 0;
//   //   delegate->flowerStateChanged(this, state);
//   // }

//   if (activation > 0 && state != ACTIVE) // From calling to active
//   {
//     state = ACTIVE;
//     delegate->flowerStateChanged(this, state);
//   }

//   // if (activation >= explotionThreshold && state == ACTIVE) // From active to silent by explosion
//   // {
//   //   state = SILENT;
//   //   activation = 0;
//   //   delegate->flowerStateChanged(this, state);
//   //   delegate->flowerExplode();
//   // }

//   activation -= activationDecay;
//   activation = max(activation, 0.0f);
// }

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

// void FlowerState::changeState(FlowerStates state)
// {
//   this->state = state;
//   delegate->flowerStateChanged(this, state);

// }

void FlowerState::changeState(FlowerStates state)
{

  this->state = state;
  delegate->flowerStateChanged(this, state);

  // Serial.printf("                                              Flower [%i] State [%i]\n", peerId, state);

  switch (state)
  {
  case SILENT:
    countdownSilentToCalling = 4; //random(1, 4);
    track->stop();
    activation = 0;

    // CHANGE animation

    break;

  case CALLING:
    countdownCallingToSilent = 4; //random(4, 32); // reset silent

    track->radomize();
    track->play();

    // Change animation
    break;

  case ACTIVE:
    countdownActiveToSilent = 4;

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

    // if (random(3) > 1)
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
    // flowerState->activeUpdate();
    // countdown to go from active to silent
    // when the countdown reaches 0, goes to silent
    countdownActiveToSilent--;
    if (countdownActiveToSilent <= 0)
    {
      changeState(SILENT);
    }

    // there is a count up to stop acrtivation (explosion) when condition is met (touch)
    // if counter reaches threshold, go to silent
    // check if activation > explosion_th... and change to silent if
    // if (activation >= explosionThreshold)
    // {
    //   /* code */
    //   changeState(ACTIVE);
    // }

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

    if (random(10) > 5)
    {
      changeState(ACTIVE);
    }

    if (activation >= activationThreshold)
    {
      /* code */
      changeState(ACTIVE);
    }

    break;
  case ACTIVE:

    if (activation >= explosionThreshold)
    {
      /* code */
      changeState(ACTIVE);
    }

    break;

  default:
    break;
  }
}