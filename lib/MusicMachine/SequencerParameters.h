#pragma once
#include "Parameter.h"
#include <Arduino.h>

namespace HLMusicMachine
{
  enum ArpeggioType
  {
    ArpeggioType_Eucledian,
    ArpeggioType_LFO
  };

  struct Parameters
  {
    Parameter<uint8_t> steps = {16, 1, 16};
    Parameter<uint8_t> events = {4, 1, 16};
    Parameter<uint8_t> offset = {0, 0, 16};
    Parameter<uint8_t> stepLenght = {4, 12, 0};

    Parameter<int8_t> octave = {1, 0, 10};
    Parameter<uint8_t> noteCount = {1, 1, 7};
    Parameter<uint8_t> noteSpread = {1, 1, 5};
    Parameter<uint8_t> noteOffset = {0, 0, 20};
    Parameter<ArpeggioType> arpeggioType = {ArpeggioType_Eucledian, ArpeggioType_Eucledian, ArpeggioType_LFO};
    Parameter<uint8_t> arpeggioLFO = {3, 1, 32};

    Parameter<bool> chord = {false, false, true};

    Parameter<int8_t> retrig = {0, -1, 10}; // 0 is disable -1 is auto with lfo
    Parameter<uint8_t> retrigLFO = {1, 1, 16};
    Parameter<uint8_t> retrigMin = {3, 0, 16};
    Parameter<uint8_t> retrigMax = {8, 0, 16};

    Parameter<uint8_t> velocityMax = {127, 0, 127};
    Parameter<uint8_t> velocityMin = {0, 0, 127};
    Parameter<bool> velocityLFOEnabled = {false, false, true};
    Parameter<uint8_t> velocityLFOSpeed = {1, 1, 16};
  };
}