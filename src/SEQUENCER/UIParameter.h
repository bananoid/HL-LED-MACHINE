#pragma once
#include <Arduino.h>
#include "UIComponent.h"

template <typename T>
class UIParameter : UIComponent
{
public:
  T *value;
  T min;
  T max;
  void draw() override
  {
    int val = constrain(value, min, max);
    int barValW = map(val, min, max, 0, w - 2);
    ctx->drawRect(x + 1, y + 1, barValW, 3, color);
    ctx->setFont(Font5x7FixedMono);
    ctx->setTextSize(1);
    ctx->setTextColor(color);
    ctx->setCursor(x + 1, y + h - 2);
    ctx->print(val);
  }
};
