#pragma once

#include <LinkedList.h>
#include "Scale.hpp"

#include "Instrument.h"
#include "SequenceGenerator.h"

#include "Sequencer.h"

using namespace MusicTheory;

namespace HLSequencer
{
  class Sequencer;
  class Track
  {
  public:
    int gridSize = 24;

    int retrigSize = 6;
    bool retrig = false;

    Sequencer *sequencer;

    Instrument *instrument;
    Track(Sequencer *sequencer, Instrument *instrument);

    LinkedList<SequenceGenerator *> *sequences;
    void appendSequence(SequenceGenerator *sequence);

    void clockTick(int counter);
  };
}
