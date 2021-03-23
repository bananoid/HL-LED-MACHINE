#pragma once

#include "GFXUtils.h"

namespace LEDSynth
{
  class LEDStripsRenderer
  {
  private:
  public:
    LEDStripsRenderer();
    ~LEDStripsRenderer();

    virtual void begin();
    virtual void setPixel(int inx, fRGB color);
    virtual void show();
  };

}
