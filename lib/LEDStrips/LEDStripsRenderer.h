#ifndef HL_LIB_LEDSTRIPS_LEDSTRIPSRENDERER
#define HL_LIB_LEDSTRIPS_LEDSTRIPSRENDERER

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
