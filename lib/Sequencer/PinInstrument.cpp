#include "PinInstrument.h"
namespace HLSequencer
{
  PinIntrument::PinIntrument(int pin, Scheduler *runner) : Instrument(runner, 1)
  {
    this->pin = pin;
    pinMode(pin, OUTPUT);

    voices[0]->trigTime = TASK_MILLISECOND * 30;
  }

  void PinIntrument::noteOn(int note, int vel)
  {
    // analogWrite(pin, trigPWM);

    // ledcWrite(pin, trigPWM);

    Serial.printf("Trig on %i\n", pin);
    digitalWrite(pin, HIGH);
  }

  void PinIntrument::noteOff(int note)
  {
    // analogWrite(pin, 0);

    Serial.printf("Trig off %i\n", pin);
    // ledcWrite(pin, 0);
    digitalWrite(pin, LOW);
  }
}