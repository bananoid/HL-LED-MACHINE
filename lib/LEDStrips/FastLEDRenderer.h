#ifndef HL_LIB_LEDSTRIPS_FASTLEDRENDERER
#define HL_LIB_LEDSTRIPS_FASTLEDRENDERER

#include "LEDStripsRenderer.h"
#include <FastLED.h>

namespace LEDStrips
{

  class FastLEDRenderer : public LEDStripsRenderer
  {
  private:
  public:
    struct CRGB *leds;

    FastLEDRenderer();
    ~FastLEDRenderer();

    void begin() override;
    void setPixel(int inx, GFXUtils::fRGB color) override;
    void show() override;
  };

} // namespace LEDStrips
#endif /* HL_LIB_LEDSTRIPS_FASTLEDRENDERER */
