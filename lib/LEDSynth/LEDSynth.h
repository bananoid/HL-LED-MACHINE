#pragma once

#include <LEDStripsRenderer.h>
#include <GFXUtils.h>

namespace LEDSynth
{

  class LEDSynth
  {
  private:
  public:
    LEDStrips::LEDStripsRenderer *renderer;
    LEDSynth(LEDStrips::LEDStripsRenderer *renderer);
    void update();
  };

} // namespace LEDSynth
