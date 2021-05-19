#pragma once

#include "Scale.hpp"
#include "MusicTheory.hpp"

#include "Instrument.h"
#include "Tracker.h"

using namespace MusicTheory;

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

    enum ArpeggioType
    {
      ArpeggioType_Eucledian,
      ArpeggioType_LFO
    };

    struct Step
    {
      int note = 1;
      int velocity = 127;
    };

    struct Parameters
    {
      int steps = 16;
      int events = 4;
      int offset = 0;

      int stepLenght = 4;

      int octave = 3;
      int noteCount = 4;
      int noteSpread = 2;
      int noteOffset = 0;
      ArpeggioType arpeggioType = ArpeggioType_Eucledian;
      int arpeggioLFO = 3;

      int chord = 0;

      int retrig = 0; // 0 is disable -1 is auto with lfo
      float retrigLFO = 32;
      int retrigLFOMin = 1;
      int retrigLFOMax = 8;

      int velocity = 127; // -1 enable lfo
      float velocityLFO = 16;
      int velocityLFOMin = 30;
      int velocityLFOMax = 127;

      float fillFactor = 1; // 0 - 1 percentange of notes that are pick from sequence
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

  private:
    int lastStepInx = 0;
    Step lastStep;
    int onCounter = 0;
  };
}
