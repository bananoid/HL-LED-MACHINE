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
  UITrackPlotter(Track *track)
  {
    this->track = track;
  };

  void draw() override
  {
    // auto seq = track->sequencers[0];
    // auto size = seq->parameters.steps;

    // float stepSize = frame.h / (float)size;

    // for (int i = 0; i < size; i++)
    // {
    //   bool isOn = seq->isEuclidean(i);
    //   if (!isOn)
    //   {
    //     continue;
    //   }
    //   float pos = i * stepSize;
    //   ctx->drawRect({0, (int)pos, frame.w, (int)stepSize}, COLOR_CYAN_F, true);
    // }

    auto tick = masterClock->tickCounter;
    auto buffer = &track->instrument->eventsBuffer;
    using index_t = decltype(track->instrument->eventsBuffer)::index_t;

    for (index_t i = 0; i < buffer->size(); i++)
    {
      auto event = (*buffer)[i];

      float pos = (tick - event.startTick) * scale;

      float size = (event.noteLenght) * scale - 1;
      size = max(size, 1);

      float vSize = event.vel / 128.f * (float)frame.w;
      vSize = max(vSize, 2);
      float vPos = frame.w / 2.0f - vSize / 2.0f;
      // if (pos > frame.h)
      // {
      //   break;
      // }
      ctx->drawRect({vPos, frame.h - (int)pos, (int)vSize, (int)size}, COLOR_CYAN_F, true);
    }
  }
};
