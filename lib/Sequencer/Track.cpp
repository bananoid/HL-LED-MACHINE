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
      float oscA = sinf(counter * 0.012442);
      oscA = asinf(oscA) / HALF_PI;
      retrigSize = map(oscA, -1.f, 1.f, 1.f, 24.f);
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
      Note note = sequencer->getNote((step->note % 4) * 3, 3);
      int midiNote = note.getMIDINoteNumber();
      instrument->noteOn(midiNote, (timeInx % 4) * 40 + 30, 100);
    }
  }
}