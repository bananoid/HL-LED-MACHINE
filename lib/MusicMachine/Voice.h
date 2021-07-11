#pragma once

#include "config.h"
#include <TaskSchedulerDeclarations.h>

namespace HLMusicMachine
{
  class VoiceDelegate
  {
  public:
    virtual long getClockTime();
    virtual void noteOn(uint8_t note, uint8_t vel, uint8_t voiceIndex);
    virtual void noteOff(uint8_t note, uint8_t voiceIndex);
  };

  class Voice
  {
  public:
    Voice(Scheduler *runner);
    VoiceDelegate *delegate;

    Task voiceTask;

    uint8_t index = 0;

    long trigTime = 0;

    int lastNote;
    virtual void noteOn(int note, int vel, int noteLenght);
    virtual void noteOff(int note = 0);
  };
}