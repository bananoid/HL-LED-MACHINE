#pragma once

#include <LinkedList.h>
#include "Scale.hpp"

#include "Instrument.h"
#include "SequenceGenerator.h"
#include "EuclideanSequence.h"
#include "Sequencer.h"

using namespace MusicTheory;

namespace HLSequencer
{
  class Sequencer;
  class Track
  {
  public:
    int gridSize = 24;
    int retrig = 0;

    Sequencer *sequencer;
    EuclideanSequence *generator;

    Instrument *instrument;
    Track(Sequencer *sequencer, Instrument *instrument);

    void clockTick(int counter);
  };
}
