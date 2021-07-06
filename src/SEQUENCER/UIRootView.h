#pragma once

#include "UIScrollView.h"
#include <Tracker.h>
#include "UIClockView.h"
#include "UIHarmonyView.h"
#include "UITracksView.h"

class UIRootView : public UIScrollView
{
private:
public:
  Tracker *tracker;
  UIRootView(Tracker *tracker)
  {
    this->tracker = tracker;
  }

  void build() override
  {
    layoutType = HORIZONTAL;

    UIView *cView;
    auto itemFrame = frame;
    for (int i = 0; i < 3; i++)
    {
      cView = new UIHarmonyView(tracker);
      cView->frame = itemFrame;
      cView->label = String(i);
      addChild(cView);
    }

    cView = new UIClockView(tracker);
    cView->frame = itemFrame;
    addChild(cView);

    cView = new UITracksView(tracker);
    cView->frame = itemFrame;
    addChild(cView);
  }
};