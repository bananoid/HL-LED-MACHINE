#pragma once

#include <LEDStripsRenderer.h>
#include <GFXUtils.h>

#define _TASK_OO_CALLBACKS
#include <TaskSchedulerDeclarations.h>

namespace LEDSynth
{
  class LEDSynth : public Task
  {
  private:
  public:
    int numberOfPixel = 12;
    unsigned long position = 0;
    unsigned long lastFrameTime = 0;
    int index = 0;
    LEDStrips::LEDStripsRenderer *renderer;
    LEDSynth(int numberOfPixel, LEDStrips::LEDStripsRenderer *renderer, Scheduler *runner);
    void update();

    bool Callback();

    void syncTo(unsigned long position);
  };

} // namespace LEDSynth
