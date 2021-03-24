#pragma once

#include "LEDShader.h"
#include <vector>

using namespace std;

namespace LEDSynth
{
  class LEDShaderDiffusion : LEDShader
  {
  private:
    vector<fRGB> buffer;

  public:
    float speed = 1;
    int bufferSize;

    LEDShaderDiffusion(int bufferSize)
    {
      this->bufferSize = bufferSize;
      buffer.reserve(bufferSize);

      for (int i = 0; i < bufferSize; i++)
      {
        buffer[i] = fRGB(0, 0, 0);
      }
    }

    int pointToPixel(float pointPosition)
    {
      int inx = pointPosition * ((float)bufferSize);
      inx = (bufferSize + (inx % bufferSize)) % bufferSize;
      return inx;
    }

    void trig(float pointPosition, fRGB color)
    {
      int inx = pointToPixel(pointPosition);
      buffer[inx] = color;
    }

    void update(float deltaTime) override
    {
      fRGB color;
      for (int i = 0; i < bufferSize; i++)
      {
        color = buffer[i];

        int prevInx = i - 1 < 0 ? bufferSize : i - 1;
        fRGB prevColor = buffer[prevInx];

        int nextInx = i + 1 >= bufferSize ? 0 : i + 1;
        fRGB nextColor = buffer[nextInx];

        float difFac = 0.02f;
        color = color * (1.0f - difFac) + GFXUtils::absC((nextColor - color)) * difFac;
        color = color * (1.0f - difFac) + GFXUtils::absC((prevColor - color)) * difFac;

        // color = color * (1 - 0.04);

        // buffer[i] = GFXUtils::clamp01(color);
        buffer[i] = color;
      }
    }

    fRGB colorAtPosition(float position)
    {
      // TODO: return linear interpolation color between pixel
      return fRGB();
    }

    fRGB renderPoint(float pointPosition, float time) override
    {
      int inx = pointToPixel(pointPosition);
      return buffer[inx];
    }
  };
}