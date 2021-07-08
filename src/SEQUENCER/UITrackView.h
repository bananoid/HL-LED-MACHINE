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
    itemFrame.y = 96;
    itemFrame.h -= itemFrame.y;

    itemFrame.x = 0;
    cView = new UISequencerParameters(track->sequencers[0]);
    cView->frame = itemFrame;
    cView->focusColor = COLOR_YELLOW_F;
    addChild(cView);

    itemFrame.x = frame.w / 2;
    cView = new UISequencerParameters(track->sequencers[0]);
    cView->frame = itemFrame;
    cView->focusColor = COLOR_YELLOW_F;
    addChild(cView);
  }

  void update()
  {
    if (ctx->controller->buttonKeys[KEY_ID_SCREEN_A]->pressed())
    {
      track->togglePlayStop();
    }
  }

  void draw() override
  {
    Rect onOffBox = {0, 0, frame.w, 16};
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
    ctx->drawText(label, frame.w / 2, 11, ALIGN_CENTER);
  }
};
