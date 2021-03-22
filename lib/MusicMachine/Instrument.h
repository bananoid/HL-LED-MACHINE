#pragma once

#include "config.h"
// #define _TASK_TIMEOUT
#include <TaskSchedulerDeclarations.h>

#include <vector>
#include "Voice.h"

namespace HLMusicMachine
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

    bool isEnabled = false;
    void toggleEnabled();

    void trigNote(int note = 0, int vel = 127, int noteLenght = 0);

    virtual void noteOn(int note = 0, int vel = 127);
    virtual void noteOff(int note = 0);
    virtual void randomize();

    long getClockTime() override;
  };
}