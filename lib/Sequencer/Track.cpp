#include "Track.h"

namespace HLSequencer
{
  Track::Track(Instrument *instrument)
  {
    this->instrument = instrument;
    suqences = new LinkedList<SequenceGenerator *>();
  }

  void Track::appendSequence(SequenceGenerator *sequnce)
  {
    suqences->add(sequnce);
  }
}