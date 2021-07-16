#pragma once
#include "Parameter.h"
#include <Arduino.h>

namespace HLMusicMachine
{
  enum ArpeggioType
  {
    ArpeggioType_Eucledian,
    ArpeggioType_RetrigFollow,
    ArpeggioType_LFO,
  };

  struct Parameters
  {
    Parameter<uint8_t> steps = {16, 1, 16};
    Parameter<uint8_t> events = {4, 1, 16};
    Parameter<uint8_t> offset = {0, 0, 16};
    Parameter<uint8_t> stepLenght = {4, 12, 0};

    Parameter<int8_t> octave = {1, 0, 10};
    Parameter<uint8_t> noteCount = {1, 1, 7};
    Parameter<uint8_t> noteSpread = {1, 1, 10};
    Parameter<uint8_t> noteOffset = {0, 0, 20};
    Parameter<ArpeggioType> arpeggioType = {ArpeggioType_Eucledian, ArpeggioType_Eucledian, ArpeggioType_LFO};
    Parameter<uint8_t> arpeggioLFO = {3, 1, 22};

    Parameter<bool> chord = {false, false, true};

    Parameter<uint8_t> retrig = {0, 0, 10};
    Parameter<bool> retrigLFOEnabled = {false, false, true};
    Parameter<uint8_t> retrigLFO = {8, 1, 16};
    Parameter<uint8_t> retrigMin = {3, 0, 16};
    Parameter<uint8_t> retrigMax = {8, 0, 16};

    Parameter<uint8_t> velocityMax = {127, 0, 127};
    Parameter<uint8_t> velocityMin = {0, 0, 127};
    Parameter<uint8_t> velocityLFOSpeed = {0, 0, 16};
    Parameter<float> velocityLFOPhase = {0, 0, 1};
    Parameter<float> velocityLFOQue = {0.5, 0.001, 3};
    Parameter<float> velocityLFOSym = {0.5, 0, 1};
  };
}