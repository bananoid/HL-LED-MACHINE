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

    template <typename T>
    struct Parameter
    {
      T value;
      T min;
      T max;

      inline Parameter operator=(T v)
      {
        value = v;
        return *this;
      }

      inline operator T() const
      {
        return value;
      }

      inline operator&() const
      {
        return &value;
      }
    };

    struct Parameters
    {
      Parameter<uint8_t> steps = {16, 1, 16};
      Parameter<uint8_t> events = {4, 1, 16};
      Parameter<uint8_t> offset = {0, 1, 16};
      Parameter<uint8_t> stepLenght = {4, 9, 1};

      Parameter<int8_t> octave = {3, -1, 4};
      Parameter<uint8_t> noteCount = {4, 1, 7};
      Parameter<uint8_t> noteSpread = {2, 1, 5};
      Parameter<uint8_t> noteOffset = {0, 0, 6};
      Parameter<ArpeggioType> arpeggioType = {ArpeggioType_Eucledian, ArpeggioType_Eucledian, ArpeggioType_LFO};
      Parameter<uint8_t> arpeggioLFO = {3, 1, 32};

      Parameter<bool> chord = {false, false, true};

      Parameter<int8_t> retrig = {0, -1, 7}; // 0 is disable -1 is auto with lfo
      Parameter<float> retrigLFO = {32, 1, 8};

      Parameter<int8_t> velocity = {127, -1, 127}; // -1 enable lfo
      Parameter<float> velocityLFO = {16, 30, 127};

      Parameter<float> fillFactor = {1, 0, 1}; // 0 - 1 percentange of notes that are pick from sequence
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
