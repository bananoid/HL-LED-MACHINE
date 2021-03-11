#pragma once
#include <Arduino.h>
#include "Instrument.h"

namespace HLSequencer
{
  class MIDIInstrument : public Instrument
  {
  public:
    int channel;
    MIDIInstrument(int channel, Scheduler *runner);

    void noteOn(int note = 0, int vel = 127, int autoReleaseLength = 1) override;
    void noteOff(int note) override;
  };
}