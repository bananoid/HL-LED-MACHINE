#pragma once

#include "UIView.h"
#include "UISequencerParameters.h"
#include <Track.h>

using namespace HLMusicMachine;

class UITrackView : public UIView
{
private:
public:
  Track *track;
  UITrackView(Track *track)
  {
    this->track = track;
  }

  void build() override
  {
    UIView *cView;
    auto itemFrame = frame;
    itemFrame.w /= 2;
    itemFrame.x = 0;
    itemFrame.y = 0;
    // itemFrame.h = 48;
    // itemFrame.y = frame.h - itemFrame.h;
    cView = new UISequencerParameters(track->sequencers[0]);
    cView->frame = itemFrame;
    addChild(cView);
  }
};
