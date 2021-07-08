#pragma once
#include "UIView.h"
#include "UIParameterView.h"
#include <Track.h>
#include "UIDisplayConfig.h"
#include "UITrackView.h"
using namespace HLMusicMachine;

class UITrackCollView : public UIView
{
public:
  Track *track;
  UITrackView *trackView;

  UITrackCollView(Track *track)
  {
    this->track = track;

    trackView = new UITrackView(track);
  }

  void build() override
  {
  }

  void update() override
  {
  }

  void draw() override
  {
    Rect onOffBox = {1, frame.h - 15, 30, 14};

    auto textColor = COLOR_BLACK_B;
    if (track->isPlaying)
    {
      ctx->drawRect(onOffBox, COLOR_YELLOW_F, true);
    }
    else
    {
      ctx->drawRect(onOffBox, COLOR_CYAN_B);
      textColor = COLOR_WHITE_F;
    }

    ctx->setTextSize(1);
    ctx->setTextColor(textColor);
    ctx->setCursor(0, 0);
    ctx->drawText(label, frame.w / 2, onOffBox.y + 11, ALIGN_CENTER);
  }

  UIView *getSubView() override
  {
    return trackView;
  };
};