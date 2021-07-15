#pragma once
#include <Arduino.h>
#include "UIView.h"
#include "GFX_fonts/Font5x7FixedMono.h"
// #include <Sequencer.h>
#include <Parameter.h>
#include <ssd1351.h>
#include <MathUtils.h>
#include "config.h"
#include <typeinfo>

using namespace HLMusicMachine;

template <typename T>
class UIParameterView : public UIView
{
private:
public:
  Parameter<T> *param;
  UIParameterView(Parameter<T> *param)
  {
    this->param = param;
    focusColor = COLOR_GREEN_F;
  }

  void update() override
  {
    if (isFocused())
    {
      auto wheelSpeed = ctx->controller->wheelEncoders[WHEEL_ID_RIGHT]->speed;
      if (wheelSpeed != 0)
      {
        auto wheelPressed = ctx->controller->buttonKeys[KEY_ID_WHEEL_RIGHT]->isPressed();

        if (param->min > param->max)
        {
          wheelSpeed *= -1;
        }

        if (wheelPressed)
        {
          wheelSpeed *= abs(param->max - param->min) / 10;
        }

        updateParam(param, wheelSpeed);
      }
    }
  }

  void updateParam(Parameter<bool> *param, float wheelSpeed)
  {
    *param = !*param;
  }

  void updateParam(Parameter<uint8_t> *param, float wheelSpeed)
  {
    *param += wheelSpeed;
  }

  void updateParam(Parameter<int8_t> *param, float wheelSpeed)
  {
    *param += wheelSpeed;
  }

  void updateParam(Parameter<float> *param, float wheelSpeed)
  {
    float delta = abs(param->max - param->min);

    wheelSpeed *= delta * 0.01f;

    *param += wheelSpeed;
  }

  void updateParam(Parameter<Sequencer::ArpeggioType> *param, float wheelSpeed)
  {
    *param += wheelSpeed;
  }

  void draw() override
  {
    int barValW = param->scale(0, frame.w - 2);

    // ctx->drawRect({1, 1, frame.w - 2, frame.h - 2}, COLOR_RED_B, true);
    ctx->drawRect({1, 1, barValW, 3}, COLOR_RED_F, true);
    ctx->setTextSize(1);
    ctx->setTextColor(COLOR_WHITE_F);
    ctx->setCursor(0, 0);
    ctx->drawText(label, 4, frame.h - 16, ALIGN_LEFT);
    ctx->drawText(String(*param), frame.w / 2, frame.h - 2, ALIGN_LEFT);
  }
};