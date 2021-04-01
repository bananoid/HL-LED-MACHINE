#pragma once
#include <Arduino.h>
#include "Instrument.h"

namespace HLMusicMachine
{
  class MIDIInstrument : public Instrument
  {
  public:
    int channel;
    MIDIInstrument(int channel, Scheduler *runner, int voiceCount = 4);

    void noteOn(int note = 0, int vel = 127, uint8_t voiceIndex = 0) override;
    void noteOff(int note, uint8_t voiceIndex = 0) override;
    void randomize() override;
  };
}