#pragma once
#include <Arduino.h>
#include <vector>

namespace HLMusicMachine
{

  class NoteQuantizer
  {
  private:
  public:
    uint16_t curretBinScale;
    bool keys[12];
    std::vector<uint8_t> curretScale;

    NoteQuantizer()
    {
      setCurrentScale(0b111111111111);
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
      // Serial.print("curScale = ");
      // for (auto n : curretScale)
      // {
      //   Serial.printf("[%i] ", n);
      // }
      // Serial.println("");

      auto size = curretScale.size();
      if (size == 0)
      {
        return 0;
      }

      octave += inx / size;
      inx = inx % size;
      return constrain(curretScale[inx] + octave * 12, 0, 257);
    };

    void toggleNoteInx(uint8_t inx)
    {
      keys[inx] = !keys[inx];
      setCurrentScale(keys);
    }
  };
}