#pragma once

#include "Tracker.h"
#include "Instrument.h"
#include "Sequencer.h"

#include <list>
#include <iterator>

using namespace std;

namespace HLMusicMachine
{
  class Sequencer;
  class Tracker;
  class Track
  {
  public:
    Tracker *tracker;
    Instrument *instrument;
    list<Sequencer *> sequencers;

    Track(Tracker *tracker, Instrument *instrument);
    Sequencer *addSequencer();

    void clockTick(int counter);
    void radomize();

    bool isPlaying = false;
    void play();
    void stop();
  };
}