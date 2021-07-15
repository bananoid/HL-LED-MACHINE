#include "GlobalSettings.h"

// #include <iostream>
// #include <SequencerParameters.h>
// #include "config.h"
// using namespace HLMusicMachine;

std::istream &operator>>(std::istream &os, const GlobalSettings gs)
{
  for (int i = 0; i < NUM_OF_CV_TRAKS; i++)
  {
    os >> gs.trackParams[i]; // >> gs.tracksEnabled[i];
  }

  return os;
}
