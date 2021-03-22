#pragma once
#include <Arduino.h>

namespace HLMusicMachine
{

  class SequenceGenerator
  {
  public:
    // int counter;

    virtual bool isOn(int index);
  };
}