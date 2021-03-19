#pragma once

#include <Arduino.h>

#include "config.h"
#include <TaskSchedulerDeclarations.h>
#include "Clock.h"
#include <LinkedList.h>
#include "Track.h"
#include "Scale.hpp"

using namespace MusicTheory;

namespace HLSequencer
{
  class Track;
  class Sequencer : public ClockDelegate, public InstrumentDelegate
  {
  private:
    LinkedList<Track *> *tracks;

  public:
    Sequencer(Scheduler *runner);
    Clock *clock;
    void clockTick() override;

    void appendTrack(Track *track);

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
