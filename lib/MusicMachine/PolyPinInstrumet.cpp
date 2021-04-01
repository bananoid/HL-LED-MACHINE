#include "PolyPinInstrumet.h"
#include <Arduino.h>

namespace HLMusicMachine
{
  PolyPinInstrumet::PolyPinInstrumet(Scheduler *runner, const uint8_t *pins, int voiceCount) : Instrument(runner, voiceCount)
  {
    for (uint8_t i = 0; i < voiceCount; i++)
    {
      pinMode(pins[i], OUTPUT);
      this->pins[i] = pins[i];

      voices[i]->trigTime = TASK_MILLISECOND * 50;
    }
  }

  void PolyPinInstrumet::noteOn(int note, int vel, uint8_t voiceIndex)
  {
    if (!isEnabled)
    {
      return;
    }
    int pin = pins[voiceIndex];
    Serial.printf("noteOn vx:%i pin:%i\n", voiceIndex, (int)pin);

    digitalWrite(pin, HIGH);
  }

  void PolyPinInstrumet::noteOff(int note, uint8_t voiceIndex)
  {
    int pin = pins[voiceIndex];
    digitalWrite(pin, LOW);
  }
}