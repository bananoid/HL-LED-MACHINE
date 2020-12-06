#pragma once

#include <LEDStripsRenderer.h>
#include <GFXUtils.h>

namespace LEDSynth
{

  class LEDSynth
  {
  private:
  public:
    unsigned long position = 0;
    unsigned long lastFrameTime = 0;
    int index = 0;
    LEDStrips::LEDStripsRenderer *renderer;
    LEDSynth(LEDStrips::LEDStripsRenderer *renderer);
    void update();
  };

} // namespace LEDSynth
