#pragma once
#include "UIView.h"
#include "UIParameterView.h"
#include <Track.h>
#include "UIDisplayConfig.h"
using namespace HLMusicMachine;

class UITrackCollView : public UIView
{
public:
  Track *track;
  UITrackCollView(Track *track)
  {
    this->track = track;
  }
  void build() override
  {
    // UIParameterView<uint8_t> *paramView;

    // paramView = new UIParameterView<uint8_t>(&track->sequencers[0]->parameters.stepLenght);
    // paramView->label = "SLen";
    // addChild(paramView);

    // paramView = new UIParameterView<uint8_t>(&track->sequencers[0]->parameters.events);
    // paramView->label = "Evts";
    // addChild(paramView);

    // paramView = new UIParameterView<uint8_t>(&track->sequencers[0]->parameters.offset);
    // paramView->label = "Ofst";
    // addChild(paramView);

    // int itInx = 0;
    // for (auto *item : childs)
    // {
    //   item->frame.h = 32;
    //   item->frame.w = frame.w;
    //   item->frame.x = 0;
    //   item->frame.y = itInx * item->frame.h;
    //   itInx++;
    // }
  }

  void update() override
  {
    // if (ctx->controller->buttonKeys[keyId]->pressed())
    // {
    //   track->togglePlayStop();
    // }
  }

  void draw() override
  {
    Rect onOffBox = {1, frame.h - 15, 30, 14};

    auto textColor = COLOR_BLACK_B;
    if (track->isPlaying)
    {
      ctx->drawRect(onOffBox, COLOR_CYAN_F, true);
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
};