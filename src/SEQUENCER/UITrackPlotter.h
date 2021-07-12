#pragma once
#include "UIPlotter.h"

#include "Track.h"
#include "Instrument.h"
#include "Clock.h"
using namespace HLMusicMachine;

class UITrackPlotter : public UIPlotter
{
private:
public:
  Track *track;
  uint8_t scaleFactor;
  UITrackPlotter(Track *track)
  {
    this->track = track;
    setScaleFactor(3);
  };
  void update()
  {
  }

  void setScaleFactor(int16_t f)
  {
    scaleFactor = constrain(f, 0, 4);
    scale = powf(2.0f, scaleFactor) / 4.0f;
  }

  void draw() override
  {
    auto tick = masterClock->tickCounter;
    auto buffer = &track->instrument->eventsBuffer;

    if (buffer->size() <= 0)
    {
      return;
    }

    float eFS;
    float vFS;
    if (direction == HORIZONTAL)
    {
      eFS = frame.h;
      vFS = frame.w;
    }
    else
    {
      eFS = frame.w;
      vFS = frame.h;
    }

    ctx->setTextSize(1);
    ctx->setTextColor(COLOR_BLACK_F);
    ctx->setCursor(0, 0);

    for (int i = buffer->size() - 1; i >= 0; i--)
    {
      auto event = (*buffer)[i];

      float pos = (tick - event.startTick) * scale;

      float size = (event.noteLenght) * scale - 1;
      size = max(size, 1);

      float vSize = event.vel / 128.f * (float)eFS;
      vSize = max(vSize, 2);
      float vPos = eFS / 2.0f - vSize / 2.0f;

      pos = vFS - pos;
      if (pos + size < 0)
      {
        break;
      }

      Rect bar = {(int)vPos, (int)pos, (int)vSize, (int)size};

      if (direction == HORIZONTAL)
      {
        bar = {(int)pos, (int)vPos, (int)size, (int)vSize};
      }

      ctx->drawRect(bar, COLOR_CYAN_F, true);

      if (bar.w > 14 && bar.h > 10)
      {
        if (direction == VERTICAL)
        {
          ctx->drawText(String(event.noteInx), bar.x + bar.w / 2, bar.y + 9, ALIGN_CENTER);
        }
        else
        {
          ctx->drawText(String(event.noteInx), bar.x + 1, bar.y + bar.h / 2 + 3, ALIGN_LEFT);
        }
      }
    }
  }
};
