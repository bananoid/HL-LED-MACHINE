#pragma once
#include "UIView.h"
#include "UIScrollView.h"
#include "UIItemView.h"
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
    auto sView = new UIScrollView();
    sView->frame = {frame.w / 2, 35, frame.w / 2, frame.h - 63};
    sView->layoutType = UIScrollView::VERTICAL;
    addChild(sView);

    for (int i = 0; i < 10; i++)
    {
      auto v = new UIItemView();
      v->frame = {0, 0, 30, 20};
      v->label = String(i);
      sView->addChild(v);
    }
  }

  void update() override
  {
  }

  void draw() override
  {
    ctx->setTextColor(COLOR_WHITE_F);
    ctx->setCursor(0, 0);
    ctx->setTextSize(2);
    ctx->drawText(label, 2, 24, ALIGN_LEFT);

    // float t = millis();
    // float o = sin(t * 0.00139) * 30;
    // float os = cos(t * 0.004234) * 10;

    // Rect rectA = {10 + os, 50 + o, 40, 30};
    // Rect rectB = {20, 60, 30, 50};
    // ctx->drawRect(rectA, COLOR_CYAN_F);

    // auto intRect = rectA.interserctWith(rectB);
    // if (intRect.w > 0 && intRect.h > 0)
    // {
    //   ctx->drawRect(rectA.interserctWith(rectB), COLOR_RED_F);
    // }

    // ctx->drawRect(rectB, COLOR_YELLOW_F);
  }
};
