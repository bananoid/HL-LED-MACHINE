#pragma once
#include <Arduino.h>
#include <vector>
#include "Parameter.h"
#include "Clock.h"
#include <CircularBuffer.h>

namespace HLMusicMachine
{

  class NoteQuantizer
  {
  private:
  public:
    uint16_t curretBinScale;
    bool keys[12];
    std::vector<uint8_t> curretScale;

    Parameter<int8_t> noteOffset = {0, -5, 5};
    int8_t tqNoteOffset = 0;

    CircularBuffer<int8_t, 32> noteOffsetRec;
    bool isRecording = false;
    uint8_t recBuffetTime = 0;

    NoteQuantizer()
    {
      setCurrentScale(0b001001001001);
    };

    void setCurrentScale(uint16_t scale)
    {
      curretBinScale = scale;
      curretScale.clear();

      for (uint8_t i = 0; i < 12; i++)
      {
        bool noteOn = (scale >> i) & 1;
        // Serial.printf("Note inx %i = %i\n", i, noteOn ? 1 : 0);
        if (noteOn || scale == 0)
        {
          curretScale.push_back(i);
        }
        keys[i] = noteOn;
      }
    };

    void setCurrentScale(bool keys[12])
    {
      curretScale.clear();

      for (auto i = 0; i < 12; i++)
      {
        this->keys[i] = keys[i];
        if (keys[i])
        {
          curretScale.push_back(i);
        }
      }
    }

    int getMidiNote(int inx, int octave)
    {
      auto size = curretScale.size();
      if (size == 0)
      {
        return 0;
      }

      inx += tqNoteOffset;

      octave += inx / size;
      inx = inx % size;
      return constrain(curretScale[inx] + octave * 12, 0, 257);
    };

    void toggleNoteInx(uint8_t inx)
    {
      keys[inx] = !keys[inx];
      setCurrentScale(keys);
    }

    void clockTick()
    {
      if ((masterClock->tickCounter) % (masterClock->clockDivider) == 0)
      {
        if (masterClock->tickCounter == 0)
        {
          recBuffetTime = 0;
        }

        recBuffetTime = recBuffetTime % 32;

        tqNoteOffset = noteOffset;

        if (isRecording)
        {
          noteOffsetRec.push(noteOffset);
        }
        else if (recBuffetTime < noteOffsetRec.size())
        {
          tqNoteOffset = noteOffsetRec[recBuffetTime];
        }

        recBuffetTime++;
      }
    }
    void toggleRecordingNoteOffset()
    {
      isRecording = !isRecording;
    }
    void setRecordingNoteOffset(bool rec)
    {
      isRecording = rec;
    }
  };
}