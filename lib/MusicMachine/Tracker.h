#pragma once

#include <Arduino.h>

#include "config.h"
#include <TaskSchedulerDeclarations.h>
#include "Clock.h"
#include "Sequencer.h"
#include "Scale.hpp"
#include "Track.h"

#include <list>
#include <iterator>

using namespace std;
using namespace MusicTheory;

namespace HLMusicMachine
{
  class Track;
  class Tracker : public ClockDelegate, public InstrumentDelegate
  {
  private:
    list<Track *> tracks;

  public:
    Tracker(Scheduler *runner);
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
