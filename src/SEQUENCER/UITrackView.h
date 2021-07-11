#pragma once

#include "UIView.h"
#include "UISequencerParameters.h"
#include <Track.h>
#include "UITrackPlotter.h"

using namespace HLMusicMachine;

class UITrackView : public UIView
{
private:
public:
  Track *track;
  UITrackPlotter *plotter;
  UISequencerParameters *seqA;
  UISequencerParameters *seqB;
  UITrackView(Track *track)
  {
    this->track = track;
  }

  void build() override
  {
    auto itemFrame = frame;
    itemFrame.w /= 2;
    itemFrame.y = 96;
    itemFrame.h -= itemFrame.y;

    plotter = new UITrackPlotter(track);
    plotter->direction = UITrackPlotter::HORIZONTAL;
    plotter->frame = {0, 16, frame.w, frame.h - itemFrame.h - 16};
    addChild(plotter);

    itemFrame.x = 0;
    seqA = new UISequencerParameters(track->sequencers[0]);
    seqA->frame = itemFrame;
    seqA->focusColor = COLOR_YELLOW_F;
    addChild(seqA);

    itemFrame.x = frame.w / 2;
    seqB = new UISequencerParameters(track->sequencers[0]);
    seqB->frame = itemFrame;
    seqB->focusColor = COLOR_YELLOW_F;
    addChild(seqB);
  }

  void update()
  {
    if (ctx->controller->buttonKeys[KEY_ID_SCREEN_A]->pressed())
    {
      track->togglePlayStop();
    }

    if (ctx->controller->buttonKeys[KEY_ID_SCREEN_B]->pressed())
    {
      focusIn(1);
    }

    if (ctx->controller->buttonKeys[KEY_ID_SCREEN_C]->pressed())
    {
      focusIn(2);
    }

    if (ctx->controller->buttonKeys[KEY_ID_SCREEN_D]->pressed())
    {
      setFocusIndex(0);
      setFocus();
    }

    if (plotter->isFocused())
    {
      auto rightWheelSpeed = ctx->controller->wheelEncoders[WHEEL_ID_RIGHT]->speed;
      if (rightWheelSpeed != 0)
      {
        plotter->setScaleFactor(plotter->scaleFactor + rightWheelSpeed);
      }
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
