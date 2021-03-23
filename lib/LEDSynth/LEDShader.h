#pragma once

#include "GFXUtils.h"

namespace LEDSynth
{
  class LEDShader
  {
  private:
  public:
    enum BlendingMode
    {
      BACKGROUND,
      NORMAL,
      ADD,
      MULTIPLY
    };
    BlendingMode blendingMode = NORMAL;
    bool enabled = true;

    float scale = 1;
    float speed = 1;

    virtual fRGB renderPoint(float position, float t)
    {
      return fRGB();
    }
  };

}