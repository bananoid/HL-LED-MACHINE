#pragma once

#include "config.h"
// #define _TASK_TIMEOUT
#include <TaskSchedulerDeclarations.h>

#include <vector>
#include "Voice.h"

namespace HLSequencer
{
  class InstrumentDelegate
  {
  public:
    virtual long getClockTime();
  };

  class Instrument : VoiceDelegate
  {
  private:
    int lastNote = -1;

  public:
    Instrument(Scheduler *runner, int voiceCount = 1);
    InstrumentDelegate *delegate;

    std::vector<Voice *> voices;
    int voiceIndex = 0;

    const int minTrigTime = 1 * TASK_MILLISECOND;
    const int maxTrigTime = 100 * TASK_MILLISECOND;
    long trigTime = TASK_MILLISECOND * 30;

    bool isEnabled = false;
    void toggleEnabled();

    void trigNote(int note = 0, int vel = 127, int noteLenght = 0);

    virtual void noteOn(int note = 0, int vel = 127);
    virtual void noteOff(int note = 0);

    long getClockTime() override;
  };
}