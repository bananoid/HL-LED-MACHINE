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

    void noteOn(int note, int vel) override;
    void noteOff(int note) override;
  };
}