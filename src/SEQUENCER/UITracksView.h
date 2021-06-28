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
    uint16_t activeKeys[] = {KEY_ID_SCREEN_A, KEY_ID_SCREEN_B, KEY_ID_SCREEN_C, KEY_ID_SCREEN_D};

    uint8_t tInx = 0;
    for (auto *track : tracker->tracks)
    {
      uint16_t activeKey = activeKeys[tInx % 4];
      trackView = new UITrackCollView(track, activeKey); // todo asign button key to track
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
  }
};
