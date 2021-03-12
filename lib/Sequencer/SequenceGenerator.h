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
    Step lastStep;
    int lastIndex = -1;
    virtual bool isOn(int index);
  };
}