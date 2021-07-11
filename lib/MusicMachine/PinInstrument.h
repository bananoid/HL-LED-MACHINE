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

    void noteOn(uint8_t note = 0, uint8_t vel = 127, uint8_t voiceIndex = 0) override;
    void noteOff(uint8_t note, uint8_t voiceIndex = 0) override;
  };
}