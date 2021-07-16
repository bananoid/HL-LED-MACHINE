#pragma once

// #include <iostream>

#include <SequencerParameters.h>
#include "config.h"
using namespace HLMusicMachine;

struct GlobalSettings
{
  Parameters trackParams[NUM_OF_CV_TRAKS];
  bool tracksEnabled[NUM_OF_CV_TRAKS];
};