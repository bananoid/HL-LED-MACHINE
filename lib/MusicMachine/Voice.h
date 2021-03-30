#pragma once

#include "config.h"
#include <TaskSchedulerDeclarations.h>

namespace HLMusicMachine
{
  class VoiceDelegate
  {
  public:
    virtual long getClockTime();
    virtual void noteOn(int note, int vel);
    virtual void noteOff(int note);
  };

  class Voice
  {
  public:
    Voice(Scheduler *runner);
    VoiceDelegate *delegate;

    Task voiceTask;

    long trigTime = 0;

    int lastNote;
    virtual void noteOn(int note, int vel, int noteLenght);
    virtual void noteOff(int note = 0);
  };
}