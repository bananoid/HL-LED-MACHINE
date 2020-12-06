#ifndef HL_LIB_LEDSTRIPS_LEDSTRIPSRENDERER
#define HL_LIB_LEDSTRIPS_LEDSTRIPSRENDERER

#define LS_NUM_LEDS_PER_STRIP 16
#define LS_NUM_STRIPS 1
#define LS_DATA_PIN 2

#include <GFXUtils.h>

namespace LEDStrips
{
  class LEDStripsRenderer
  {
  private:
  public:
    LEDStripsRenderer();
    ~LEDStripsRenderer();

    virtual void begin();
    virtual void setPixel(int inx, GFXUtils::fRGB color);
    virtual void show();
  };

} // namespace LEDStrips
#endif /* HL_LIB_LEDSTRIPS_LEDSTRIPSRENDERER */
