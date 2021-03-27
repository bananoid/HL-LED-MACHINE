#pragma once

#include "LEDShader.h"

namespace LEDSynth
{
  class LEDShaderSynth : LEDShader
  {
  private:
  public:
    struct LEDShaderSynthState
    {
      float scale = 1.f;
      float speed = 1.f;

      float que = 2.3f;
      float sym = 0.9f;
      float fmAmo = 4.f;
      float fmFrq = 1.f;

      float hue = 0.55f;
      float hueRad = 0.1f;
      float intensity = 1;
      // float hueSpeed = 2.f;

      float saturation = 1.0f;

      float audioIntensity = 1;

      float audioInfluence = 1;
    };

    LEDShaderSynthState state;
    LEDShaderSynthState *targetState;
    float interpolationSpeed = 1;

    float position;

    LEDShaderSynth()
    {
      position = 0;
      targetState = new LEDShaderSynthState();
    }

    void update(float deltaTime) override
    {
      position += deltaTime * state.speed;
      interpolateState();
    }

    void interpolateState()
    {
      state.scale += (targetState->scale - state.scale) * interpolationSpeed;
      state.speed += (targetState->speed - state.speed) * interpolationSpeed;

      state.que += (targetState->que - state.que) * interpolationSpeed;
      state.sym += (targetState->sym - state.sym) * interpolationSpeed;

      state.fmAmo += (targetState->fmAmo - state.fmAmo) * interpolationSpeed;
      state.fmFrq += (targetState->fmFrq - state.fmFrq) * interpolationSpeed;

      state.hue += (targetState->hue - state.hue) * interpolationSpeed;
      state.hueRad += (targetState->hueRad - state.hueRad) * interpolationSpeed;
      state.saturation += (targetState->saturation - state.saturation) * interpolationSpeed;

      state.intensity += (targetState->intensity - state.intensity) * interpolationSpeed;

      // state.hueSpeed += (state.hueSpeed - targetState.hueSpeed) * interpolationSpeed;
    }

    fRGB renderPoint(float pointPosition, float time) override
    {
      float pixPos = position + pointPosition * state.scale;

      float hue = 0;
      float saturation = 1;
      float intensity;

      fRGB color;

      intensity = GFXUtils::waveFM(
          pixPos,
          state.que,
          state.sym,
          state.fmAmo,
          state.fmFrq);

      saturation = 1;

      saturation = GFXUtils::clamp(saturation, 0.f, 1.f);

      hue = state.hue + sinf(fmodf(pixPos * 2.234 + time, TWO_PI)) * state.hueRad;

      color = GFXUtils::hsv(hue, saturation * state.saturation, intensity * state.intensity);

      fRGB tColor = color;
      tColor.mult(intensity * intensity * intensity);
      color.add(tColor);

      color = color * state.intensity;

      // color = color * audioIntensity;

      return color;
    }
  };

}