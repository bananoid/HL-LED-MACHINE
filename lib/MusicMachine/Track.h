#pragma once

#include "Tracker.h"
#include "Instrument.h"
#include "Sequencer.h"

#include <vector>

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
    vector<Sequencer *> sequencers;

    Track(Tracker *tracker, Instrument *instrument);
    Sequencer *addSequencer();
    Sequencer *getSequencerAt(int inx);

    void clockTick(int counter);
    void radomize();
    void setFillFactor(float fillFactor);

    bool isPlaying = false;
    void play();
    void stop();
    void togglePlayStop();
  };
}