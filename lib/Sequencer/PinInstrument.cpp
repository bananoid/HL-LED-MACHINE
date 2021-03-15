#include "PinInstrument.h"

namespace HLSequencer
{
  PinIntrument::PinIntrument(int pin, Scheduler *runner) : Instrument(runner, 1)
  {
    this->pin = pin;
    pinMode(pin, OUTPUT);
  }

  void PinIntrument::noteOn(int note, int vel)
  {
    analogWrite(pin, trigPWM);
  }

  void PinIntrument::noteOff(int note)
  {
    analogWrite(pin, 0);
  }
}