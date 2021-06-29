#pragma once
#include "UIView.h"
#include <Tracker.h>

using namespace HLMusicMachine;

class UIClockView : public UIView
{
public:
  Tracker *tracker;
  UIClockView(Tracker *tracker)
  {
    this->tracker = tracker;
  }
  void build() override
  {
  }
  void update() override
  {
    float wheelSpeed = ctx->controller->wheelEncoders[WHEEL_ID_RIGHT]->speed;
    if (ctx->controller->buttonKeys[KEY_ID_WHEEL_RIGHT]->isPressed())
    {
      wheelSpeed /= 10.0;
    }
    if (wheelSpeed != 0)
    {
      auto bpm = tracker->clock->getBpm();
      tracker->clock->setBpm(bpm + wheelSpeed);
    }
  }
  void draw() override
  {
    // ctx->drawRect({1, 1, frame.w - 2, frame.h - 2}, COLOR_RED_B, true);
    ctx->setTextColor(COLOR_WHITE_F);
    ctx->setCursor(0, 0);
    ctx->setTextSize(2);
    ctx->drawText("CLOCK", frame.w / 2, 24, ALIGN_CENTER);
    ctx->setCursor(0, 0);
    ctx->setTextSize(2);
    ctx->drawText(String(tracker->clock->getBpm()), frame.w / 2, frame.h / 2, ALIGN_CENTER);

    ctx->setCursor(0, 0);
    ctx->setTextSize(2);

    auto onBeat = tracker->clock->tickCounter % (24) == 0;
    ctx->drawCircle({frame.w / 2, frame.h - 28, 16, 0}, COLOR_RED_F, onBeat);
    if (tracker->clock->isPlaying)
    {
      ctx->drawText(">", frame.w / 2 + 1, frame.h - 20, ALIGN_CENTER);
    }
    else
    {
      ctx->drawText("||", frame.w / 2, frame.h - 20, ALIGN_CENTER);
    }
  }
};
