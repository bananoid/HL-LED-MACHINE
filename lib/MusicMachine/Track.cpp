#include "Track.h"

namespace HLMusicMachine
{
  Track::Track(Tracker *tracker, Instrument *instrument)
  {
    this->tracker = tracker;
    this->instrument = instrument;
  }

  Sequencer *Track::addSequencer()
  {
    Sequencer *sequencer = new Sequencer(tracker, instrument);
    sequencers.push_back(sequencer);
    return sequencer;
  }

  void Track::clockTick(int counter)
  {
    list<Sequencer *>::iterator it;
    Sequencer *seq;
    for (it = sequencers.begin(); it != sequencers.end(); ++it)
    {
      seq = *it;
      seq->clockTick(counter);
    }
  }
}