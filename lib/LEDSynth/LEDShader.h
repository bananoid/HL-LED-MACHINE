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
      NORMAL,
      ADD,
      MULTIPLY
    };
    BlendingMode blendingMode = NORMAL;
    bool enabled = true;

    virtual void update(float deltaTime);
    virtual fRGB renderPoint(float pixelPosition, float time);
  };
}