#pragma once
#include "UIScrollView.h"
#include "UITrackCollView.h"
#include "UITrackView.h"
#include <Tracker.h>

using namespace HLMusicMachine;

class UITracksView : public UIScrollView
{
public:
  Tracker *tracker;
  const uint16_t screenKeys[NUMBER_OF_SCREEN_KEYS] = {KEY_ID_SCREEN_A, KEY_ID_SCREEN_B, KEY_ID_SCREEN_C, KEY_ID_SCREEN_D};

  UITracksView(Tracker *tracker)
  {
    this->tracker = tracker;
    layoutType = HORIZONTAL;
    pageSize = 4;
  }
  void build() override
  {

    UITrackCollView *trackView;

    uint8_t tInx = 0;
    for (auto *track : tracker->tracks)
    {
      trackView = new UITrackCollView(track);
      trackView->label = "T" + String(tInx + 1);
      trackView->frame.w = 32;
      addChild(trackView);
      tInx++;
    }
  }

  void update()
  {

    for (int i = 0; i < NUMBER_OF_SCREEN_KEYS; i++)
    {
      auto keyId = screenKeys[i];
      if (ctx->controller->buttonKeys[keyId]->pressed())
      {
        if (ctx->controller->buttonKeys[KEY_ID_FRONT_RIGHT]->isPressed())
        {
          gotoPage(i);
        }
        else
        {
          auto nTraks = tracker->tracks.size();

          auto trackInx = i + constrain(scrollIndex, 0, nTraks - NUMBER_OF_SCREEN_KEYS);

          trackInx = constrain(trackInx, 0, nTraks - 1);
          auto track = tracker->tracks[trackInx];

          track->togglePlayStop();
        }
      }
    }
  }

  void draw() override
  {
  }
};
