#pragma once
#include "Instrument.h"
#include "SequenceGenerator.h"
#include <LinkedList.h>

namespace HLSequencer
{
  class Track
  {
  public:
    Instrument *instrument;
    Track(Instrument *instrument);
    LinkedList<SequenceGenerator *> *sequences;
    void appendSequence(SequenceGenerator *sequence);
  };
}