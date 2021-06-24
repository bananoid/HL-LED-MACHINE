#pragma once
#include <Arduino.h>
#include "UIView.h"
#include "GFX_fonts/Font5x7FixedMono.h"
#include <Sequencer.h>
#include <ssd1351.h>

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

    ctx->drawRect({1, 1, frame.w - 2, frame.h - 2}, COLOR_RED_B, true);
    ctx->drawRect({1, 1, barValW, 3}, COLOR_RED_F, true);
    ctx->setFont(Font5x7FixedMono);
    ctx->setTextSize(1);
    ctx->setTextColor(COLOR_WHITE_F);
    ctx->setCursor(1, frame.h - 2);
    ctx->drawText(String(param->value), frame.w / 2, frame.h - 2, ALIGN_CENTER);
  }
};