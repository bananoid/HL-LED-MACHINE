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
      item->color = color;
      item->frame.x = frame.x;
      item->frame.w = 32;
      item->frame.h = 16;
      item->frame.y = frame.y + itInx * item->frame.h;
      itInx++;
    }
  }
  void draw() override
  {
    if (track->isPlaying)
    {
      ctx->fillRect(frame.x + 1, frame.y + frame.h - 15, 30, 14, color);
    }
    else
    {
      ctx->drawRect(frame.x + 1, frame.y + frame.h - 15, 30, 14, color);
    }
  }
};