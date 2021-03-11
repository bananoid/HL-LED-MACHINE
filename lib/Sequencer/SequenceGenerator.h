#pragma once
#include <Arduino.h>

namespace HLSequencer
{
  struct Step
  {
    int note = 1;
    int velocity = 127;
  };

  class SequenceGenerator
  {
  public:
    int counter;
    virtual Step *isOn(int index);
  };
}