#pragma once

#include "LEDStripsRenderer.h"
#include "GFXUtils.h"

#define _TASK_OO_CALLBACKS
#include <TaskSchedulerDeclarations.h>

#include <list>
#include <iterator>

#include "LEDShader.h"
#include "LEDShaderSynth.h"

using namespace std;

namespace LEDSynth
{
  class LEDSynth : public Task
  {
  private:
  public:
    list<LEDShader *> shaders;

    int numberOfPixel = 12;
    unsigned long position = 0;
    unsigned long lastFrameTime = 0;
    int index = 0;
    LEDStripsRenderer *renderer;
    LEDSynth(int numberOfPixel, LEDStripsRenderer *renderer, Scheduler *runner);
    void update();

    bool Callback();

    void appendShader(LEDShader *shader);
    LEDShaderSynth *addLEDShaderSynth(LEDShader::BlendingMode blendingMode = LEDShader::ADD);

    void syncTo(unsigned long position);
  };

}
