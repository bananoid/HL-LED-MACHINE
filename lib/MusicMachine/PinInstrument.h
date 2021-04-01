#pragma once
#include <Arduino.h>
#include "Instrument.h"

namespace HLMusicMachine
{
  class PinIntrument : public Instrument
  {
  public:
    int pin;
    PinIntrument(int pin, Scheduler *runner);

    const int minTrigPWM = 150;
    const int maxTrigPWM = 255;
    int trigPWM = 255;

    void noteOn(int note = 0, int vel = 127, uint8_t voiceIndex = 0) override;
    void noteOff(int note, uint8_t voiceIndex = 0) override;
  };
}