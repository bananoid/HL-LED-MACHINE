#pragma once
#include <Arduino.h>
// #include <UI.h>

#include <ssd1351.h>
#include "GFX_fonts/Font5x7FixedMono.h"

typedef ssd1351::HighColor Color;
typedef ssd1351::SSD1351<Color, ssd1351::SingleBuffer, 128, 128> Display;

class UIComponents
{
public:
  struct UIState
  {
    int x = 0;
    int y = 0;
    int w = 32;
    int h = 16;
  };

  struct ParamState : UIState
  {
    String label;
    // int8_t value;
    int value;
    int min = 0;
    int max = 100;
  };

  static void drawParam(Display *ctx, ParamState state)
  {
    int val = constrain(state.value, state.min, state.max);
    int barValW = map(val, state.min, state.max, 0, state.w - 2);
    ctx->drawRect(state.x + 1, state.y + 1, barValW, 3, ssd1351::RGB(255, 0, 0));
    ctx->setFont(Font5x7FixedMono);
    ctx->setTextSize(1);
    ctx->setTextColor(ssd1351::RGB(255, 0, 0));
    // ctx->setCursor(state.x, state.y);
    ctx->setCursor(state.x + 1, state.y + state.h - 2);
    ctx->print(val);
    // ctx->printf("%d", state.value);
  }
};