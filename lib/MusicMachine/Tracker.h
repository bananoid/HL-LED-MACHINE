#pragma once

#include <Arduino.h>

#include "config.h"
#include <TaskSchedulerDeclarations.h>
#include "Clock.h"
#include "Sequencer.h"
#include "Parameter.h"
#include "Scale.hpp"
#include "Track.h"
#include "NoteQuantizer.h"
#include <vector>
#include <iterator>
using namespace std;

using namespace MusicTheory;

namespace HLMusicMachine
{
  class Track;

  class TrackerDelegate
  {
  public:
    virtual void trackerBarTick();
  };

  class Tracker : public ClockDelegate, public InstrumentDelegate
  {
  private:
  public:
    vector<Track *> tracks;
    Tracker(Scheduler *runner);
    Scheduler *runner;

    TrackerDelegate *delegate = nullptr;

    Clock *clock;
    void clockTick() override;
    void clockStart() override;
    void clockStop() override;

    void appendTrack(Track *track);

    long getClockTime() override;

    Scale *currentScale = nullptr;
    NoteType currentKey;
    void pickNextHarmony();
    int harmonyCounter = 0;
    int progressionInterval = 3;
    int progressionIntervalCounter = 0;

    int getNote(int inx, int octave);
    int scaleIndex = 0;
    void setScaleIndex(int i);

    int keyIndex = 0;
    void setKeyIndex(int i);

    NoteQuantizer *quantizer;

    Parameter<uint8_t> noteOffset = {0, 0, 20};
  };
}
