#include "PinInstrument.h"

PinIntrument::PinIntrument(int pin, Scheduler *runner) : Instrument(runner)
{
  this->pin = pin;
  pinMode(pin, OUTPUT);
}

void PinIntrument::noteOn(int note, int vel)
{
  Instrument::noteOn(note, vel);
  analogWrite(pin, trigPWM);
}

void PinIntrument::noteOff(int note)
{
  Instrument::noteOff(note);
  analogWrite(pin, 0);
}