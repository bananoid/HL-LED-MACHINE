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
    auto rightWheelSpeed = ctx->controller->wheelEncoders[WHEEL_ID_RIGHT]->speed;
    if (rightWheelSpeed != 0)
    {
      setScaleFactor(scaleFactor + rightWheelSpeed);
    }
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

    for (int i = buffer->size() - 1; i >= 0; i--)
    {
      auto event = (*buffer)[i];

      float pos = (tick - event.startTick) * scale;

      float size = (event.noteLenght) * scale - 1;
      size = max(size, 1);

      float vSize = event.vel / 128.f * (float)frame.w;
      vSize = max(vSize, 2);
      float vPos = frame.w / 2.0f - vSize / 2.0f;

      pos = frame.h - pos;
      if (pos + size < 0)
      {
        break;
      }
      ctx->drawRect({vPos, (int)pos, (int)vSize, (int)size}, COLOR_CYAN_F, true);
    }
  }
};
