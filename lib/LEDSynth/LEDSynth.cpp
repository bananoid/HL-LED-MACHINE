#include "LEDSynth.h"

#include <Arduino.h>

namespace LEDSynth
{

  LEDSynth::LEDSynth(int numberOfPixel, LEDStripsRenderer *renderer, Scheduler *runner)
  {
    this->renderer = renderer;
    this->numberOfPixel = numberOfPixel;

    calculatePixelScale(1);

    updateTask.set(16 * TASK_MILLISECOND, TASK_FOREVER, [this]() {
      update();
    });
    runner->addTask(updateTask);
    updateTask.enable();
  }

  void LEDSynth::calculatePixelScale(float scaleFactor)
  {
    pixelScale = scaleFactor / numberOfPixel;
  }

  // bool LEDSynth::Callback()
  // {
  //   update();
  //   return true;
  // }

  void LEDSynth::appendShader(LEDShader *shader, LEDShader::BlendingMode blendingMode)
  {
    shaders.push_back(shader);
    if (shaders.size() == 1)
    {
      shader->blendingMode = LEDShader::NORMAL;
    }
    else
    {
      shader->blendingMode = blendingMode;
    }
  }

  LEDShaderSynth *LEDSynth::addLEDShaderSynth(LEDShader::BlendingMode blendingMode)
  {
    LEDShaderSynth *shader = new LEDShaderSynth();
    appendShader((LEDShader *)shader, blendingMode);
    return shader;
  }

  LEDShaderDiffusion *LEDSynth::addLEDShaderDiffusion(LEDShader::BlendingMode blendingMode)
  {
    LEDShaderDiffusion *shader = new LEDShaderDiffusion(numberOfPixel);
    appendShader((LEDShader *)shader, blendingMode);
    return shader;
  }

  void LEDSynth::update()
  {
    unsigned long curTime = millis();
    float time = curTime / 1000.0f;
    float deltaTime = (curTime - lastFrameTime) / 1000.0f;
    lastFrameTime = curTime;

    float pointPosition;

    LEDShader *shader;
    list<LEDShader *>::iterator it;

    for (it = shaders.begin(); it != shaders.end(); ++it)
    {
      shader = *it;
      shader->update(deltaTime);
    }

    for (size_t i = 0; i < numberOfPixel; i++)
    {
      fRGB color = {0, 0, 0};

      for (it = shaders.begin(); it != shaders.end(); ++it)
      {
        shader = *it;
        pointPosition = i * pixelScale;

        fRGB sColor = shader->renderPoint(pointPosition, time);
        if (shader->blendingMode == LEDShader::ADD)
        {
          color.add(sColor);
        }
        else if (shader->blendingMode == LEDShader::MULTIPLY)
        {
          color.mult(sColor);
        }
        else if (shader->blendingMode == LEDShader::MULTIPLY_GRAY)
        {
          color.mult(sColor.r);
        }
        else
        {
          color = sColor;
        }
      }

      renderer->setPixel(i, color);
    }
    renderer->show();
  }
}
