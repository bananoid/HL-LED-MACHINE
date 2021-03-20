#include "FastLEDRenderer.h"

#include <FastLED.h>

namespace LEDStrips
{

  FastLEDRenderer::FastLEDRenderer()
  {
  }

  FastLEDRenderer::~FastLEDRenderer()
  {
  }

  void FastLEDRenderer::begin(CRGB *leds, int numberOfPixel)
  {
    this->leds = leds;
    this->numberOfPixel = numberOfPixel;

    FastLED.setDither(0);
    FastLED.setBrightness(255);
  }

  void FastLEDRenderer::setPixel(int inx, GFXUtils::fRGB color)
  {
    leds[inx] = CRGB(color.r * 255, color.g * 255, color.b * 255);
  }
  void FastLEDRenderer::show()
  {
    FastLED.show();
  }

} // namespace LEDStrips