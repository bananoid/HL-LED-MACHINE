#include "Track.h"

namespace HLMusicMachine
{
  Track::Track(Tracker *tracker, Instrument *instrument)
  {
    this->tracker = tracker;
    this->instrument = instrument;
  }

  void Track::play()
  {
    isPlaying = true;
    instrument->isEnabled = true;
  }
  void Track::stop()
  {
    isPlaying = false;
    instrument->isEnabled = false;
  }
  void Track::togglePlayStop()
  {
    if (isPlaying)
    {
      stop();
    }
    else
    {
      play();
    }
  }

  Sequencer *Track::addSequencer()
  {
    Sequencer *sequencer = new Sequencer(tracker, instrument);
    sequencers.push_back(sequencer);
    return sequencer;
  }
  Sequencer *Track::getSequencerAt(int inx)
  {
    return sequencers[inx];
  }

  void Track::clockTick(int counter)
  {
    for (Sequencer *seq : sequencers)
    {
      seq->clockTick(counter);
    }
  }

  void Track::radomize()
  {
    for (Sequencer *seq : sequencers)
    {
      seq->randomize();
    }
  }

  void Track::setFillFactor(float fillFactor)
  {
    for (Sequencer *seq : sequencers)
    {
      seq->parameters.fillFactor = fillFactor;
    }
  }
}