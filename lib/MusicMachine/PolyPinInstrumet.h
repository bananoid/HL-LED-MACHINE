#pragma once
#include <Arduino.h>
#include "Instrument.h"

namespace HLMusicMachine
{
  class PolyPinInstrumet : public Instrument
  {
  public:
    uint8_t pins[3];
    PolyPinInstrumet(Scheduler *runner, const uint8_t *pins, int voiceCount = 3);

    void noteOn(int note = 0, int vel = 127, uint8_t voiceIndex = 0) override;
    void noteOff(int note, uint8_t voiceIndex = 0) override;
  };
}