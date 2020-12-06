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

  void FastLEDRenderer::begin()
  {
    leds = new CRGB[LS_NUM_LEDS_PER_STRIP * LS_NUM_STRIPS];

    FastLED.addLeds<WS2812B, LS_DATA_PIN, GRB>(leds, LS_NUM_LEDS_PER_STRIP);

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