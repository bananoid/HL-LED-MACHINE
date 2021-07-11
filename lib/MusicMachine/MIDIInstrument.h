#pragma once
#include <Arduino.h>
#include "Instrument.h"

namespace HLMusicMachine
{
  class MIDIInstrument : public Instrument
  {
  public:
    int port = 1;
    int channel;
    MIDIInstrument(int channel, Scheduler *runner, int voiceCount = 4, int port = 1);

    void noteOn(uint8_t note = 0, uint8_t vel = 127, uint8_t voiceIndex = 0) override;
    void noteOff(uint8_t note, uint8_t voiceIndex = 0) override;
    void randomize() override;
    virtual void pitchBend(double val);
  };
}