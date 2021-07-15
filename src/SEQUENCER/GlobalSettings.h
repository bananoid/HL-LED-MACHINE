#pragma once

// #include <iostream>

#include <SequencerParameters.h>
#include "config.h"
using namespace HLMusicMachine;

struct GlobalSettings
{
  Parameters trackParams[NUM_OF_CV_TRAKS];
  bool tracksEnabled[NUM_OF_CV_TRAKS];

  // std::ostream &operator<<(std::ostream &os)
  // {
  //   for (int i = 0; i < NUM_OF_CV_TRAKS; i++)
  //   {
  //     os << trackParams[i]; // << tracksEnabled[i];
  //   }

  //   return os;
  // }
};

// std::istream &operator>>(std::istream &os, const GlobalSettings gs);