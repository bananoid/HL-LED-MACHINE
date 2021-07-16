#pragma once

#include "Scale.hpp"
#include "MusicTheory.hpp"

#include "Instrument.h"
#include "Tracker.h"
#include "Parameter.h"

using namespace MusicTheory;
#include <MathUtils.h>
#include "SequencerParameters.h"

namespace HLMusicMachine
{

  class Tracker;
  class Sequencer
  {
  public:
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

    Type type = MELODY;
    Note percussionNote = Note(24);

    Parameters parameters;
    Parameters minParameters;
    Parameters maxParameters;

    void randomize();

    Tracker *tracker;

    Instrument *instrument;
    Sequencer(Tracker *tracker, Instrument *instrument);

    bool isEuclidean(int stepInx);
    static bool isEuclidean(int inx, int steps, int events, int offset);

    void clockTick(int counter);
    uint32_t lastTrigTime = 0;
    uint32_t lastEuqTrigTime = 0;

  private:
    int lastStepInx = 0;
    Step lastStep;
    int onCounter = 0;
  };
}
