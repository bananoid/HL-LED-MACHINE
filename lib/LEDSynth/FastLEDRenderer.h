#ifndef HL_LIB_LEDSTRIPS_FASTLEDRENDERER
#define HL_LIB_LEDSTRIPS_FASTLEDRENDERER

#include "LEDStripsRenderer.h"
#include <FastLED.h>

namespace LEDSynth
{

  class FastLEDRenderer : public LEDStripsRenderer
  {
  private:
  public:
    CRGB *leds;
    int numberOfPixel;

    FastLEDRenderer();
    ~FastLEDRenderer();

    void begin(CRGB *leds, int numberOfPixel);
    void setPixel(int inx, fRGB color) override;
    void show() override;
  };

} // namespace LEDStrips
#endif /* HL_LIB_LEDSTRIPS_FASTLEDRENDERER */
