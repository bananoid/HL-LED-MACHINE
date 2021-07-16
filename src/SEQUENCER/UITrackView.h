#pragma once

#include "UIView.h"
#include "UISequencerParameters.h"
#include <Track.h>
#include "UITrackPlotter.h"
#include "Storage.h"

using namespace HLMusicMachine;

class UITrackView : public UIView
{
private:
public:
  Track *track;
  UITrackPlotter *plotter;
  UISequencerParameters *seqA;
  UISequencerParameters *seqB;

  UIParameterView<uint16_t> *storeSlot;

  UITrackView(Track *track)
  {
    this->track = track;
  }

  void build() override
  {
    auto itemFrame = frame;
    // itemFrame.w /= 2;
    itemFrame.y = 80;
    itemFrame.h = 32;

    plotter = new UITrackPlotter(track);
    plotter->direction = UITrackPlotter::HORIZONTAL;
    plotter->frame = {0, 0, frame.w, frame.h - itemFrame.h - 16};
    addChild(plotter);

    itemFrame.x = 0;
    itemFrame.w = 96;
    seqA = new UISequencerParameters(track->sequencers[0]);
    seqA->frame = itemFrame;
    seqA->focusColor = COLOR_YELLOW_F;
    addChild(seqA);

    // seqB = new UISequencerParameters(track->sequencers[0]);
    // seqB->frame = itemFrame;
    // seqB->focusColor = COLOR_YELLOW_F;
    // addChild(seqB);

    itemFrame.x = itemFrame.w;
    itemFrame.w = 32;
    storeSlot = new UIParameterView<uint16_t>(&storage->tracksBank->currentSlot);
    storeSlot->frame = itemFrame;
    storeSlot->label = "Slot";
    addChild(storeSlot);
  }

  void update() override;

  void draw() override
  {
    Rect onOffBox = {0, frame.h - 16, frame.w, 16};
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
    ctx->drawText(label, 4, frame.h - 5, ALIGN_LEFT);

    if (storeSlot->isFocused() && ctx->controller->buttonKeys[KEY_ID_FRONT_RIGHT]->isPressed())
    {
      Rect btnFrame = {64, frame.h - 16, 32, 16};

      ctx->drawRect(btnFrame, COLOR_YELLOW_F, true);
      ctx->setTextColor(COLOR_BLACK_B);
      ctx->drawText("SAVE", btnFrame.x + btnFrame.w / 2, btnFrame.y + btnFrame.h - 5, ALIGN_CENTER);

      btnFrame.x += 32;

      ctx->drawRect(btnFrame, COLOR_YELLOW_F, true);
      ctx->setTextColor(COLOR_BLACK_B);
      ctx->drawText("LOAD", btnFrame.x + btnFrame.w / 2, btnFrame.y + btnFrame.h - 5, ALIGN_CENTER);
    }
  }
};
