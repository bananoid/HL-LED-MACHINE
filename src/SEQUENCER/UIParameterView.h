#pragma once
#include <Arduino.h>
#include "UIView.h"
#include "GFX_fonts/Font5x7FixedMono.h"

template <typename T>
class UIParameterView : public UIView
{
public:
  T *value;
  T min;
  T max;
  void draw() override
  {
    int val = *value;
    if (min < max)
    {
      val = constrain(*value, min, max);
    }
    else
    {
      val = constrain(*value, max, min);
    }

    int barValW = map(val, min, max, 0, frame.w - 2);

    ctx->drawRect(frame.x + 1, frame.y + 1, barValW, 3, color);
    ctx->setFont(Font5x7FixedMono);
    ctx->setTextSize(1);
    ctx->setTextColor(color);
    ctx->setCursor(frame.x + 1, frame.y + frame.h - 2);
    ctx->print(val);
    // drawText
  }
};