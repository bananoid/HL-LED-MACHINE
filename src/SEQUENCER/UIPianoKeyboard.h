#pragma once
#include "UIScrollView.h"
#include <GFXUtils.h>
#include <NoteQuantizer.h>

using namespace HLMusicMachine;
using namespace GFX;

class UIPianoKeyboard : public UIScrollView
{
private:
public:
  uint8_t keySize = 32;
  const uint8_t keyCount = 12;
  NoteQuantizer *quatizer = nullptr;

  UIPianoKeyboard(NoteQuantizer *quatizer)
  {
    pageSize = 4;
    this->quatizer = quatizer;
  }

  void update() override
  {
    if (!isFocused())
    {
      return;
    }

    auto leftWheelSpeed = ctx->controller->wheelEncoders[WHEEL_ID_LEFT]->speed;
    if (leftWheelSpeed != 0)
    {
      int16_t inx = scrollIndex + leftWheelSpeed;
      scrollIndex = constrain(inx, 0, keyCount - 4);
    }
  }

  void draw() override
  {
    const bool keysColors[12] = {1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1};
    const String keysLabels[12] = {
        "C",
        "C#",
        "D",
        "D#",
        "E",
        "F",
        "F#",
        "G",
        "G#",
        "A",
        "A#",
        "B",
    };

    // int pos = scrollInx * -keySize;

    ctx->setTextSize(1);
    ctx->setCursor(0, 0);

    for (auto i = 0; i < pageSize; i++)
    {
      uint8_t keyInx = scrollIndex + i;

      bool noteOn = false;
      if (quatizer != nullptr)
      {
        noteOn = (quatizer->curretBinScale >> keyInx) & 1;
        noteOn = quatizer->keys[keyInx];
      }

      auto keyColor = keysColors[keyInx];
      auto pos = i * keySize;

      int kW = keySize;
      int kH = frame.h;

      Rect keyBox = {pos + 1, 1, kW - 2, kH - 2};

      auto bgColor = keyColor ? COLOR_WHITE_F : COLOR_BLACK_F;
      auto textColor = keyColor ? COLOR_BLACK_F : COLOR_WHITE_F;

      if (noteOn)
      {
        bgColor = COLOR_YELLOW_F;
        textColor = COLOR_BLACK_F;
      }

      ctx->drawRect(keyBox, bgColor, true);
      ctx->setTextColor(textColor);
      ctx->drawText(keysLabels[keyInx], pos + keySize / 2, 10, ALIGN_CENTER);
    }
  }
  // void setFocusIndex(int16_t inx) override
  // {
  //   Serial.printf("focus inx %i\n", inx);
  // }
};
