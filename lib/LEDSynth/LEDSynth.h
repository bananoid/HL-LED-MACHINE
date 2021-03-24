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
    unsigned long lastFrameTime = 0;

  public:
    list<LEDShader *> shaders;

    int numberOfPixel = 12;
    float pixelScale = 0.01;

    void calculatePixelScale(float scaleFactor);

    LEDStripsRenderer *renderer;
    LEDSynth(int numberOfPixel, LEDStripsRenderer *renderer, Scheduler *runner);
    void update();

    bool Callback();

    void appendShader(LEDShader *shader, LEDShader::BlendingMode blendingMode = LEDShader::ADD);
    LEDShaderSynth *addLEDShaderSynth(LEDShader::BlendingMode blendingMode = LEDShader::ADD);

    void syncTo(float position);
  };

}
