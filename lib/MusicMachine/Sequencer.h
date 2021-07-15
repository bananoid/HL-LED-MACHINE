#pragma once

#include "Scale.hpp"
#include "MusicTheory.hpp"

#include "Instrument.h"
#include "Tracker.h"

using namespace MusicTheory;
#include <MathUtils.h>

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
    private:
      float value;

    public:
      T min;
      T max;

      Parameter(T value, T min, T max)
      {
        this->value = value;
        this->min = min;
        this->max = max;
      }

      inline Parameter operator=(T v)
      {
        value = v;
        return *this;
      }

      inline operator T() const
      {
        return (T)value;
      }

      Parameter &operator+=(const float inc)
      {
        if (min < max)
        {
          value = constrain(value + inc, (float)min, (float)max);
        }
        else
        {
          value = constrain(value + inc, (float)max, (float)min);
        }
        return *this;
      }

      float scale(float a, float b)
      {
        return MathUtils::scale((float)value, (float)min, (float)max, (float)a, (float)b);
      }
    };

    struct Parameters
    {
      Parameter<uint8_t> steps = {16, 1, 16};
      Parameter<uint8_t> events = {4, 1, 16};
      Parameter<uint8_t> offset = {0, 0, 16};
      Parameter<uint8_t> stepLenght = {4, 12, 0};

      Parameter<int8_t> octave = {1, 0, 10};
      Parameter<uint8_t> noteCount = {1, 1, 7};
      Parameter<uint8_t> noteSpread = {1, 1, 5};
      Parameter<uint8_t> noteOffset = {0, 0, 20};
      Parameter<ArpeggioType> arpeggioType = {ArpeggioType_Eucledian, ArpeggioType_Eucledian, ArpeggioType_LFO};
      Parameter<uint8_t> arpeggioLFO = {3, 1, 32};

      Parameter<bool> chord = {false, false, true};

      Parameter<int8_t> retrig = {0, -1, 10}; // 0 is disable -1 is auto with lfo
      Parameter<uint8_t> retrigLFO = {1, 1, 16};
      Parameter<uint8_t> retrigMin = {3, 0, 16};
      Parameter<uint8_t> retrigMax = {8, 0, 16};

      Parameter<uint8_t> velocityMax = {127, 0, 127};
      Parameter<uint8_t> velocityMin = {0, 0, 127};
      Parameter<bool> velocityLFOEnabled = {false, false, true};
      Parameter<uint8_t> velocityLFOSpeed = {1, 1, 16};
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
