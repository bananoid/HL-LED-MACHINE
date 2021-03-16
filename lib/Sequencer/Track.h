#pragma once

#include <LinkedList.h>
#include "Scale.hpp"
#include "MusicTheory.hpp"

#include "Instrument.h"
#include "SequenceGenerator.h"
#include "EuclideanSequence.h"
#include "Sequencer.h"

using namespace MusicTheory;

namespace HLSequencer
{
  enum Type
  {
    MELODY,
    PERCUSSION
  };

  struct Step
  {
    int note = 1;
    int velocity = 127;
  };

  class Sequencer;
  class Track
  {
  private:
    int lastStepInx = 0;
    int retrigCount = 0;
    Step lastStep;
    int onCounter = 0;

  public:
    Type type = MELODY;
    Note percussionNote = Note(24);

    int stepLenght = 24;

    // 0 is disable -1 is auto with lfo
    int retrig = 0;
    float retrigLFO = 32;
    int retrigLFOMin = 1;
    int retrigLFOMax = 8;

    int octave = 3;
    int noteCount = 4;
    int noteSpread = 2;
    int chord = 0;

    Sequencer *sequencer;
    EuclideanSequence *generator;

    Instrument *instrument;
    Track(Sequencer *sequencer, Instrument *instrument);

    void clockTick(int counter);
  };
}
