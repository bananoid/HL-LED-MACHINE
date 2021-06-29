#pragma once
#include "UIView.h"
#include <Tracker.h>

using namespace HLMusicMachine;

class UIHarmonyView : public UIView
{
public:
  Tracker *tracker;
  UIHarmonyView(Tracker *tracker)
  {
    this->tracker = tracker;
  }
  void build() override
  {
  }
  void update() override
  {
  }
  void draw() override
  {
    ctx->setTextColor(COLOR_WHITE_F);
    ctx->setCursor(0, 0);
    ctx->setTextSize(2);
    ctx->drawText("HARMONY", frame.w / 2, 24, ALIGN_CENTER);
  }
};
