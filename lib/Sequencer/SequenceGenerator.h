#pragma once
#include <Arduino.h>

namespace HLSequencer
{
  class SequenceGenerator
  {
  public:
    virtual int isOn(int index);
  };
}