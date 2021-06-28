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
    for (auto *track : tracker->tracks)
    {
      trackView = new UITrackCollView(track, 1); // todo asign button key to track
      trackView->frame.x = tInx * 32;
      trackView->frame.w = 32;
      trackView->frame.y = 16;
      trackView->frame.h = frame.h - 16;
      addChild(trackView);
      tInx++;
    }
  }
  void draw() override
  {
    // for (int i = 0; i < tracker->tracks.size(); i++)
    // {
    //   ctx->drawRect({i * 32, 0, 1, frame.h}, {0.1, 0.1, 0.1});
    // }
  }
};
