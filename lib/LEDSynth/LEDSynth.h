#pragma once

#include "LEDStripsRenderer.h"
#include "GFXUtils.h"

#define _TASK_STD_FUNCTION
#include <TaskSchedulerDeclarations.h>

#include <list>
#include <iterator>

#include "LEDShader.h"
#include "LEDShaderSynth.h"
#include "LEDShaderDiffusion.h"

using namespace std;

namespace LEDSynth
{
  class LEDSynth
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

    void appendShader(LEDShader *shader, LEDShader::BlendingMode blendingMode = LEDShader::ADD);
    LEDShaderSynth *addLEDShaderSynth(LEDShader::BlendingMode blendingMode = LEDShader::ADD);
    LEDShaderDiffusion *addLEDShaderDiffusion(LEDShader::BlendingMode blendingMode = LEDShader::ADD);

    Task updateTask;
  };
}
