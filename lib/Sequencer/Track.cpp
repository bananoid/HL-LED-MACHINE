#include "Track.h"

namespace HLSequencer
{
  Track::Track(Sequencer *sequencer, Instrument *instrument)
  {
    this->sequencer = sequencer;
    this->instrument = instrument;
    instrument->delegate = sequencer;
    generator = new EuclideanSequence();
  }

  void Track::clockTick(int counter)
  {
    int retrigSize = retrig;

    if (retrig < 0)
    {
      // TODO: parametrize retrig LFO
      float rLFO = sinf(counter * 0.012442);
      rLFO = asinf(rLFO) / HALF_PI;
      retrigSize = map(rLFO, -1.f, 1.f, 3.f, 24.f);
    }

    if ((counter) % (retrigSize > 0 ? retrigSize : gridSize) != 0)
    {
      return;
    }

    int timeInx = counter / gridSize;

    bool isOn = generator->isOn(timeInx);
    Step *step = &generator->lastStep;

    if (isOn || retrigSize > 0)
    {
      Note note = sequencer->getNote((step->note % noteCount) * noteSpread, octave);
      int midiNote = note.getMIDINoteNumber();

      // TODO: velocity modulation
      int velocity = (97.0f / gridSize * counter) + 30;
      // int velocity = 127;

      
      instrument->noteOn(midiNote, velocity, 10000);
    }
  }
}