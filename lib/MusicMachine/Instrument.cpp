#include "Instrument.h"
#include <Arduino.h>
#include <Clock.h>
namespace HLMusicMachine
{
  Instrument::Instrument(Scheduler *runner, int voiceCount)
  {
    voices.reserve(voiceCount);
    for (int i = 0; i < voiceCount; i++)
    {
      Voice *voice = new Voice(runner);
      voice->delegate = this;
      voice->index = i;
      voices.push_back(voice);
    }
  }

  void Instrument::toggleEnabled()
  {
    isEnabled = !isEnabled;
  }

  long Instrument::getClockTime()
  {
    return delegate->getClockTime();
  }

  void Instrument::trigNote(uint8_t note, uint8_t vel, uint16_t noteLenght)
  {

    if (note != lastNote)
    {
      voiceIndex++;
    }
    voiceIndex = voiceIndex % voices.size();

    lastNote = note;

    auto startTick = masterClock->tickCounter;
    eventsBuffer.push({startTick,
                       noteLenght,
                       note,
                       vel,
                       voiceIndex});

    if (!isEnabled)
    {
      return;
    }
    voices[voiceIndex]->noteOn(note, vel, noteLenght);
  }

  void Instrument::noteOn(uint8_t note, uint8_t vel, uint8_t voiceIndex)
  {
  }

  void Instrument::noteOff(uint8_t note, uint8_t voiceIndex)
  {
  }

  void Instrument::pitchBend(double val)
  {
  }

  void Instrument::randomize()
  {
  }
}