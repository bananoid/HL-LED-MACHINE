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

  void draw() override
  {

    Rect btnFrame = {1, 1, frame.w, 16};
    Color recColor = COLOR_YELLOW_F;
    Color recLabelColor = COLOR_BLACK_B;
    if (tracker->quantizer->isRecording)
    {
      recColor = COLOR_RED_F;
      recLabelColor = COLOR_WHITE_F;
    }

    ctx->setCursor(0, 0);
    ctx->setTextSize(1);
    ctx->setTextSize(1);

    ctx->drawRect(btnFrame, recColor, true);
    ctx->setTextColor(recLabelColor);
    ctx->drawText("REC", btnFrame.x + btnFrame.w / 2, btnFrame.y + btnFrame.h - 5, ALIGN_CENTER);

    ctx->setTextSize(2);
    ctx->setTextColor(COLOR_WHITE_F);
    ctx->drawText(tracker->quantizer->tqNoteOffset, btnFrame.x + btnFrame.w - 6, btnFrame.y + btnFrame.h + 20, ALIGN_RIGHT);

    ctx->setTextSize(2);
    ctx->setTextColor(COLOR_WHITE_F);
    ctx->drawText(String(tracker->quantizer->noteOffset), 4, btnFrame.y + btnFrame.h + 20, ALIGN_LEFT);

    ctx->setTextSize(2);
    ctx->setTextColor(COLOR_WHITE_F);
    ctx->drawText(String(tracker->quantizer->recBuffetTime) + "/32", 4, btnFrame.y + btnFrame.h + 40, ALIGN_LEFT);
  }
};
