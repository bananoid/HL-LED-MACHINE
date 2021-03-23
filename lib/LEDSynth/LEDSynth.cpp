#include "LEDSynth.h"

#include <Arduino.h>

namespace LEDSynth
{

  LEDSynth::LEDSynth(int numberOfPixel, LEDStripsRenderer *renderer, Scheduler *runner) : Task(16 * TASK_MILLISECOND, TASK_FOREVER, runner, true)
  {
    this->renderer = renderer;
    this->numberOfPixel = numberOfPixel;
  }

  bool LEDSynth::Callback()
  {
    update();
    return true;
  }

  void LEDSynth::appendShader(LEDShader *shader)
  {
    shaders.push_back(shader);
  }

  LEDShaderSynth *LEDSynth::addLEDShaderSynth(LEDShader::BlendingMode blendingMode)
  {
    LEDShaderSynth *shader = (new LEDShaderSynth());
    appendShader((LEDShader *)shader);
    // appendShader(shader);
    return shader;
  }

  void LEDSynth::update()
  {
    unsigned long curTime = millis();
    position += (curTime - lastFrameTime);
    lastFrameTime = curTime;

    float t = position / 1000.0f;

    LEDShader *shader;
    list<LEDShader *>::iterator it;
    float pixelPosition;
    float scale = 0.01;
    float speed = 0.1;

    fRGB color = {0, 0, 0};

    for (it = shaders.begin(); it != shaders.end(); ++it)
    {
      shader = *it;
      for (size_t i = 0; i < numberOfPixel; i++)
      {
        pixelPosition = i * scale + t * speed;

        fRGB sColor = shader->renderPoint(pixelPosition, t);
        color.add(sColor);
        renderer->setPixel(i, color);
      }
    }
    renderer->show();
  }

  void LEDSynth::syncTo(unsigned long position) //position in ms
  {
    this->position = position;
  }
}
