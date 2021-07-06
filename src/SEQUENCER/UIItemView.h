#pragma once
#include "UIView.h"

class UIItemView : public UIView
{
public:
  UIItemView()
  {
  }

  void draw() override
  {
    // ctx->drawRect({0, 0, frame.w, frame.h}, COLOR_YELLOW_F, true);
    ctx->setTextColor(COLOR_WHITE_F);
    ctx->setCursor(0, 0);
    ctx->setTextSize(1);
    ctx->drawText(label, frame.w / 2, 16, ALIGN_CENTER);
  }
};
