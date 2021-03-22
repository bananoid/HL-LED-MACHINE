#pragma once

#include "config.h"
// #define _TASK_TIMEOUT
#include <TaskSchedulerDeclarations.h>

namespace HLSequencer
{
  class VoiceDelegate
  {
  public:
    virtual long getClockTime();
    virtual void noteOn(int note, int vel);
    virtual void noteOff(int note);
  };

  class Voice : public Task
  {
  public:
    Voice(Scheduler *runner);
    VoiceDelegate *delegate;

    bool Callback();

    long trigTime = 0;

    int lastNote;
    virtual void noteOn(int note, int vel, int noteLenght);
    virtual void noteOff(int note = 0);
  };
}