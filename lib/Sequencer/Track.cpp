#include "Track.h"

namespace HLSequencer
{
  Track::Track(Instrument *instrument)
  {
    this->instrument = instrument;
    sequences = new LinkedList<SequenceGenerator *>();
  }

  void Track::appendSequence(SequenceGenerator *sequnce)
  {
    sequences->add(sequnce);
  }
}