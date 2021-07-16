#pragma once

#include "UIView.h"

#include "Storage.h"
#include "UIParameterView.h"
#include <Arduino.h>
#include <Parameter.h>
using namespace HLMusicMachine;

class UIFileManagerView : public UIView
{
private:
public:
  Parameter<uint8_t> selectedTrack = {1, 1, NUM_OF_CV_TRAKS + NUM_OF_MIDI_TRAKS};

  enum FocusMode
  {
    NONE,
    PROJECTS,
    TRACKS,
  };

  FocusMode focusMode = NONE;

  UIParameterView<uint16_t> *paramProjectSlot;
  UIParameterView<uint16_t> *paramTracksSlot;
  UIParameterView<uint8_t> *paramTrackInx;

  void build() override
  {
    auto itFrame = frame;
    itFrame.h = 32;
    itFrame.y = 16;

    {
      auto param = new UIParameterView<uint16_t>(&storage->projectsBank->currentSlot);
      param->frame = itFrame;
      param->frame.w = frame.w - 32;
      param->label = "Project Slot";
      addChild(param);
      paramProjectSlot = param;
    }

    itFrame.y += itFrame.h;

    {
      auto param = new UIParameterView<uint16_t>(&storage->tracksBank->currentSlot);
      param->frame = itFrame;
      param->frame.w = 64;
      param->label = "Slot <<";
      addChild(param);
      paramTracksSlot = param;
    }

    // itFrame.y += itFrame.h;

    {
      auto param = new UIParameterView<uint8_t>(&selectedTrack);
      param->frame = itFrame;
      param->frame.w = 64;
      param->frame.x = 64;
      param->label = ">> Track";
      addChild(param);
      paramTrackInx = param;
    }
  }

  void update() override;

  void draw() override
  {
    ctx->setCursor(0, 0);
    ctx->setTextSize(1);

    ctx->drawRect({0, 0, frame.w, 16}, COLOR_YELLOW_F, true);
    ctx->setTextColor(COLOR_BLACK_B);
    ctx->drawText("FILE MANAGER", frame.w / 2, 12, ALIGN_CENTER);

    ctx->setTextSize(2);
    ctx->setTextColor(COLOR_WHITE_F);
    ctx->drawText(String(storage->projectsBank->lastSlot), frame.w - 16, 32 + 7, ALIGN_CENTER);

    // Save Load Buttons
    if (focusMode != NONE)
    {
      ctx->setTextSize(1);
      Rect btnFrame = {1, frame.h - 16, 62, 16};

      Color slBtnBgColor = COLOR_YELLOW_F;
      String saveLabel = "SAVE";
      String loadLabel = "LOAD";

      if (focusMode == PROJECTS)
      {
        saveLabel += " P";
        loadLabel += " P";
      }
      else if (focusMode == TRACKS)
      {
        saveLabel += " T";
        loadLabel += " T";
      }

      ctx->drawRect(btnFrame, slBtnBgColor, true);
      ctx->setTextColor(COLOR_BLACK_B);
      ctx->drawText(saveLabel, btnFrame.x + btnFrame.w / 2, btnFrame.y + btnFrame.h - 5, ALIGN_CENTER);

      btnFrame.x = 64;

      ctx->drawRect(btnFrame, slBtnBgColor, true);
      ctx->setTextColor(COLOR_BLACK_B);
      ctx->drawText(loadLabel, btnFrame.x + btnFrame.w / 2, btnFrame.y + btnFrame.h - 5, ALIGN_CENTER);
    }
  }
};
