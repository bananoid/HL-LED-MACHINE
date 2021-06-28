#pragma once
#include <Arduino.h>
#include "UIView.h"
#include "GFX_fonts/Font5x7FixedMono.h"
#include <Sequencer.h>
#include <ssd1351.h>
#include <MathUtils.h>
#include "config.h"

using namespace HLMusicMachine;

template <typename T>
class UIParameterView : public UIView
{
private:
public:
  Sequencer::Parameter<T> *param;
  UIParameterView(Sequencer::Parameter<T> *param)
  {
    this->param = param;
  }

  void update() override
  {
    auto wheelSpeed = ctx->controller->wheelEncoders[WHEEL_ID_RIGHT]->speed;
    if (wheelSpeed != 0)
    {
      *param += wheelSpeed;
    }
  }

  void draw() override
  {
    int barValW = param->scale(0, frame.w - 2);

    ctx->drawRect({1, 1, frame.w - 2, frame.h - 2}, COLOR_RED_B, true);
    ctx->drawRect({1, 1, barValW, 3}, COLOR_RED_F, true);
    ctx->setFont(Font5x7FixedMono);
    ctx->setTextSize(1);
    ctx->setTextColor(COLOR_WHITE_F);
    ctx->drawText(String(param->min) + "/" + String(param->max), frame.w / 2, frame.h - 16, ALIGN_CENTER);
    ctx->drawText(String(*param), frame.w / 2, frame.h - 2, ALIGN_CENTER);
  }
};