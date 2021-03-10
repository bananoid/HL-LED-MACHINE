#pragma once
#include <Arduino.h>
#include "Instrument.h"

class PinIntrument : public Instrument
{
public:
  int pin;
  PinIntrument(int pin, Scheduler *runner);

  const int minTrigPWM = 150;
  const int maxTrigPWM = 255;
  int trigPWM = 255;

  void noteOn(int note, int vel);
  void noteOff(int note);
};
