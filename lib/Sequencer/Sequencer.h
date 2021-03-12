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

    unsigned long seed = 0;
    Scale *currentScale;
    NoteType currentKey;
    void pickNextHarmony();

    Note getNote(int inx, int octave);
  };
}
