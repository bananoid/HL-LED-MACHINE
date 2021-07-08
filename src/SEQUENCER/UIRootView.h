#pragma once

#include "UIScrollView.h"
#include <Tracker.h>
#include "UIClockView.h"
#include "UIHarmonyView.h"
#include "UITracksView.h"
#include "UITrackView.h"

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

    cView = new UITracksView(tracker);
    cView->frame = itemFrame;
    addChild(cView);

    cView = new UIHarmonyView(tracker);
    cView->frame = itemFrame;
    addChild(cView);

    cView = new UIClockView(tracker);
    cView->frame = itemFrame;
    addChild(cView);
  }
};