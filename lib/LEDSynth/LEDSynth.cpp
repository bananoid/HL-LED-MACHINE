#include "LEDSynth.h"

#include <Arduino.h>

namespace LEDSynth
{

  LEDSynth::LEDSynth(int numberOfPixel, LEDStripsRenderer *renderer, Scheduler *runner) : Task(16 * TASK_MILLISECOND, TASK_FOREVER, runner, true)
  {
    this->renderer = renderer;
    this->numberOfPixel = numberOfPixel;

    calculatePixelScale(0.1);
  }

  void LEDSynth::calculatePixelScale(float scaleFactor)
  {
    pixelScale = scaleFactor / numberOfPixel;
  }

  bool LEDSynth::Callback()
  {
    update();
    return true;
  }

  void LEDSynth::appendShader(LEDShader *shader, LEDShader::BlendingMode blendingMode)
  {
    shaders.push_back(shader);
    shader->blendingMode = blendingMode;
  }

  LEDShaderSynth *LEDSynth::addLEDShaderSynth(LEDShader::BlendingMode blendingMode)
  {
    LEDShaderSynth *shader = (new LEDShaderSynth());
    appendShader((LEDShader *)shader, blendingMode);
    return shader;
  }

  void LEDSynth::update()
  {
    unsigned long curTime = millis();
    float time = curTime / 1000.0f;
    float deltaTime = (curTime - lastFrameTime) / 1000.0f;
    lastFrameTime = curTime;

    float pixelPosition;

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
        pixelPosition = i * pixelScale;

        fRGB sColor = shader->renderPoint(pixelPosition, time);
        if (shader->blendingMode == LEDShader::ADD)
        {
          color.add(sColor);
        }
        else if (shader->blendingMode == LEDShader::MULTIPLY)
        {
          color.mult(sColor);
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

  void LEDSynth::syncTo(float position)
  {
    LEDShader *shader;
    list<LEDShader *>::iterator it;
    for (it = shaders.begin(); it != shaders.end(); ++it)
    {
      shader = *it;
      shader->position = position;
    }
  }
}
