#pragma once
#include <Arduino.h>

namespace HLSequencer
{

  class SequenceGenerator
  {
  public:
    // int counter;

    virtual bool isOn(int index);
  };
}