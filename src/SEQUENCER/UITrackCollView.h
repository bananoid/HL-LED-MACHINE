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
  uint16_t keyId = 0;
  UITrackCollView(Track *track, uint16_t keyId)
  {
    this->track = track;
    this->keyId = keyId;
  }
  void build() override
  {
    UIParameterView<uint8_t> *paramView;

    paramView = new UIParameterView<uint8_t>(&track->sequencers[0]->parameters.stepLenght);
    paramView->label = "Step Lenght";
    addChild(paramView);

    paramView = new UIParameterView<uint8_t>(&track->sequencers[0]->parameters.events);
    paramView->label = "Events";
    addChild(paramView);

    paramView = new UIParameterView<uint8_t>(&track->sequencers[0]->parameters.offset);
    paramView->label = "Offset";
    addChild(paramView);

    int itInx = 0;
    for (auto *item : childs)
    {
      item->frame.h = 32;
      item->frame.w = frame.w;
      item->frame.x = 0;
      item->frame.y = itInx * item->frame.h;
      itInx++;
    }
  }
  void draw() override
  {
    if (track->isPlaying)
    {
      ctx->drawRect({1, frame.h - 15, 30, 14}, COLOR_CYAN_F, true);
    }
    else
    {
      ctx->drawRect({1, frame.h - 15, 30, 14}, COLOR_CYAN_B);
    }

    if (ctx->controller->buttonKeys[keyId]->pressed())
    {
      track->togglePlayStop();
    }
  }
};