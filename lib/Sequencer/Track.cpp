#include "Track.h"

namespace HLSequencer
{
  Track::Track(Sequencer *sequencer, Instrument *instrument)
  {
    this->sequencer = sequencer;
    this->instrument = instrument;
    sequences = new LinkedList<SequenceGenerator *>();
  }

  void Track::appendSequence(SequenceGenerator *sequnce)
  {
    sequences->add(sequnce);
  }

  void Track::clockTick(int counter)
  {
    if ((counter) % (retrig ? retrigSize : gridSize) != 0)
    {
      return;
    }

    // float oscA = sinf(counter * 0.012442);
    // oscA = asinf(oscA) / HALF_PI;
    // retrigSize = map(oscA, -1.f, 1.f, 1.f, 24.f);

    int timeInx = counter / gridSize;

    SequenceGenerator *generator = sequences->get(0);

    bool isOn = generator->isOn(timeInx);
    Step *step = &generator->lastStep;

    if (isOn || retrig)
    {
      Note note = sequencer->getNote((step->note % 4) * 3, 3);
      int midiNote = note.getMIDINoteNumber();
      instrument->noteOn(midiNote, (timeInx % 4) * 40 + 30, 100);
    }
  }
}