#pragma once
#include "UIView.h"
#include "UITrackCollView.h"
#include <Tracker.h>

using namespace HLMusicMachine;

class UITracksView : public UIView
{
public:
  Tracker *tracker;
  UITracksView(Tracker *tracker)
  {
    this->tracker = tracker;
  }
  void build() override
  {
    UITrackCollView *trackView;

    uint8_t tInx = 0;
    for (Track *track : tracker->tracks)
    {
      trackView = new UITrackCollView(track);
      trackView->frame.x = tInx * 32;
      trackView->frame.y = 0;
      trackView->frame.w = 32;
      trackView->frame.h = frame.h;
      trackView->color = color;
      addChild(trackView);
      tInx++;
    }
  }
  void draw() override
  {
    ctx->drawRect(frame.x, frame.y, frame.w, frame.h, color);
  }
};
