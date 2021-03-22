#pragma once

#include <Arduino.h>

#include "config.h"
#include <TaskSchedulerDeclarations.h>
#include "Clock.h"
#include <LinkedList.h>
#include "Sequencer.h"
#include "Scale.hpp"

using namespace MusicTheory;

namespace HLMusicMachine
{
  class Sequencer;
  class Tracker : public ClockDelegate, public InstrumentDelegate
  {
  private:
    LinkedList<Sequencer *> *tracks;

  public:
    Tracker(Scheduler *runner);
    Clock *clock;
    void clockTick() override;

    void appendTrack(Sequencer *track);

    long getClockTime() override;

    Scale *currentScale = nullptr;
    NoteType currentKey;
    void pickNextHarmony();
    int harmonyCounter = 0;
    int progressionInterval = 3;
    int progressionIntervalCounter = 0;

    Note getNote(int inx, int octave);
  };
}
