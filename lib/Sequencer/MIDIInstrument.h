#pragma once
#include <Arduino.h>
#include "Instrument.h"

class MIDIInstrument : public Instrument
{
public:
  int channel;
  MIDIInstrument(int channel, Scheduler *runner);

  void noteOn(int note, int vel);
  void noteOff(int note);
};
