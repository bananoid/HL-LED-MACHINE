#include "PinInstrument.h"

namespace HLSequencer
{
  PinIntrument::PinIntrument(int pin, Scheduler *runner) : Instrument(runner)
  {
    this->pin = pin;
    pinMode(pin, OUTPUT);
  }

  void PinIntrument::noteOn(int note, int vel, int autoReleaseLength)
  {
    Instrument::noteOn(note, vel, autoReleaseLength);
    analogWrite(pin, trigPWM);
  }

  void PinIntrument::noteOff(int note)
  {
    Instrument::noteOff(note);
    analogWrite(pin, 0);
  }
}