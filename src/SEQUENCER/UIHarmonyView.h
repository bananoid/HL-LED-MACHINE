#pragma once
#include "UIView.h"
#include "UIScrollView.h"
#include "UIItemView.h"
#include <Tracker.h>
#include "UIPianoKeyboard.h"

using namespace HLMusicMachine;

class UIHarmonyView : public UIView
{
public:
  Tracker *tracker;
  UIPianoKeyboard *pianoKeys;
  const uint16_t screenKeys[NUMBER_OF_SCREEN_KEYS] = {KEY_ID_SCREEN_A, KEY_ID_SCREEN_B, KEY_ID_SCREEN_C, KEY_ID_SCREEN_D};

  UIHarmonyView(Tracker *tracker)
  {
    this->tracker = tracker;
  }
  void build() override
  {
    pianoKeys = new UIPianoKeyboard(tracker->quantizer);

    pianoKeys->frame = {0, frame.h - 16, frame.w, 16};
    addChild(pianoKeys);
  }

  void update() override
  {
    if (pianoKeys->isFocused())
    {
      for (int i = 0; i < NUMBER_OF_SCREEN_KEYS; i++)
      {
        auto keyId = screenKeys[i];
        if (ctx->controller->buttonKeys[keyId]->pressed())
        {
          int noteInx = pianoKeys->scrollIndex + i;
          tracker->quantizer->toggleNoteInx(noteInx);
        }
      }
    }
  }
};
