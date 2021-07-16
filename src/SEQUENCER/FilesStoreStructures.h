#pragma once

// #include <iostream>

#include <SequencerParameters.h>
#include "config.h"
using namespace HLMusicMachine;

struct ProjectStore
{
  Parameters trackParams[NUM_OF_CV_TRAKS + NUM_OF_MIDI_TRAKS];
  bool tracksEnabled[NUM_OF_CV_TRAKS + NUM_OF_MIDI_TRAKS];
};