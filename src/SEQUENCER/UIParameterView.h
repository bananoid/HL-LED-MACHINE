#pragma once
#include <Arduino.h>
#include "UIView.h"
#include "GFX_fonts/Font5x7FixedMono.h"
#include <Sequencer.h>

using namespace HLMusicMachine;

template <typename T>
class UIParameterView : public UIView
{
public:
  Sequencer::Parameter<T> *param;
  UIParameterView(Sequencer::Parameter<T> *param)
  {
    this->param = param;
  }
  void draw() override
  {
    int barValW = map(param->value, param->min, param->max, 0, frame.w - 2);

    ctx->drawRect(frame.x + 1, frame.y + 1, barValW, 3, color);
    ctx->setFont(Font5x7FixedMono);
    ctx->setTextSize(1);
    ctx->setTextColor(color);
    ctx->setCursor(frame.x + 1, frame.y + frame.h - 2);
    ctx->print(param->value);
    // drawText
  }
};