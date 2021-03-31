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
