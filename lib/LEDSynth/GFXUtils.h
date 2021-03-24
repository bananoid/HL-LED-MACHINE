#pragma once

#include <Arduino.h>
namespace LEDSynth
{

  typedef struct
  {
    uint8_t r;
    uint8_t g;
    uint8_t b;
  } RGB;

  typedef struct
  {
    uint8_t h;
    uint8_t s;
    uint8_t v;
  } HSV;

  struct fRGB
  {
    float r;
    float g;
    float b;
    fRGB()
    {
      r = 0;
      g = 0;
      b = 0;
    }
    fRGB(float i)
    {
      this->r = i;
      this->g = i;
      this->b = i;
    }

    fRGB(float r, float g, float b)
    {
      this->r = r;
      this->g = g;
      this->b = b;
    }

    void add(fRGB c)
    {
      this->r += c.r;
      this->g += c.g;
      this->b += c.b;
    }

    void mult(float v)
    {
      this->r *= v;
      this->g *= v;
      this->b *= v;
    }

    void mult(fRGB c)
    {
      this->r *= c.r;
      this->g *= c.g;
      this->b *= c.b;
    }

    static fRGB sum(fRGB a, fRGB b)
    {
      return fRGB(a.r + b.r, a.g + b.g, a.b + b.b);
    }
  };

  typedef struct
  {
    fRGB a;
    fRGB b;
    fRGB c;
    fRGB d;
  } Palette;

  class GFXUtils
  {
  public:
    static float fract(float x)
    {
      return x - ((int)x);
    }

    static float rnd(float x)
    {
      return fract((sinf(x) * 0.5 + 0.5) * 1e4);
    }

    static float clamp(float x, float minV, float maxV)
    {
      return fmin(fmax(x, minV), maxV);
    }

    static fRGB clamp01(fRGB x)
    {
      x.r = clamp(x.r, 0, 1);
      x.g = clamp(x.g, 0, 1);
      x.b = clamp(x.b, 0, 1);
      return x;
    }

    static float mix(float a, float b, float t)
    {
      return a * (1.0 - t) + b * t;
    }

    static fRGB mix(fRGB a, fRGB b, float t)
    {
      return fRGB(
          mix(a.r, b.r, t),
          mix(a.g, b.g, t),
          mix(a.b, b.b, t));
    }

    static fRGB alphaBlend(fRGB background, fRGB color)
    {
      float alpha = color.r * color.g * color.b;
      return mix(background, color, alpha);
    }

    static fRGB mult(fRGB a, fRGB b)
    {
      a.r *= b.r;
      a.g *= b.g;
      a.b *= b.b;

      return a;
    }

    static fRGB add(fRGB a, fRGB b)
    {
      a.r += b.r;
      a.g += b.g;
      a.b += b.b;

      return a;
    }

    static float smoothstep(float start, float stop, float x)
    {
      float t = clamp((x - start) / (stop - start), 0.0, 1.0);
      return t * t * (3.0 - 2.0 * t);
    }

    static float chaserNoise(float x, float density)
    {
      return rnd((int)x) > density ? 0 : 1;
    }

    static float chaserNoiseSmooth(float x, float density)
    {
      float i = (int)x;
      float f = fract(x);
      float denR = 0.05;
      float a = smoothstep(density + denR, density - denR, rnd(i));
      float b = smoothstep(density + denR, density - denR, rnd(i + 1));

      // float u = smoothstep(0, 1, f);
      return mix(a, b, f);
    }

    static float snoise(float x)
    {
      return (sinf(2.0 * x) + sinf(PI * x)) * 0.5 + 0.5;
    }

    static float pcurve(float x, float a, float b)
    {
      float k = powf(a + b, a + b) / (powf(a, a) * powf(b, b));
      return k * powf(x, a) * powf(1. - x, b);
    }

    static float wave(float x, float que, float sym)
    {
      float x2 = fmodf(fmodf(x, 1) + 1, 1);

      float q2 = powf(2.f, que);
      return pcurve(x2, q2 * (1 - sym) * 2, q2 * (sym)*2);
    }

    static float waveFM(float x, float que, float sym, float fmAmo, float fmFrq)
    {
      float fmPha = fmodf(x, TWO_PI) * fmFrq;
      float fmOsc = cosf(fmPha);

      float fm = fmOsc * fmAmo;

      return wave(fmodf(x, 1.f) * fm, que, sym);
    }

    static fRGB hsv(float h, float s, float v)
    {

      if (s <= 0)
      {
        return fRGB(v, v, v);
      }
      h = fmodf(1.0 + fmodf(h, 1.0), 1.0);
      h = h * 6.;
      float c = v * s;
      float x = (1 - abs((fmodf(h, 2.0) - 1.0))) * c;
      float m = v - c;
      float r = 0.0;
      float g = 0.0;
      float b = 0.0;

      if (h < 1)
      {
        r = c;
        g = x;
        b = 0.0;
      }
      else if (h < 2)
      {
        r = x;
        g = c;
        b = 0.0;
      }
      else if (h < 3)
      {
        r = 0.0;
        g = c;
        b = x;
      }
      else if (h < 4)
      {
        r = 0.0;
        g = x;
        b = c;
      }
      else if (h < 5)
      {
        r = x;
        g = 0.0;
        b = c;
      }
      else
      {
        r = c;
        g = 0.0;
        b = x;
      }

      return fRGB(r + m, g + m, b + m);
    }
  };
}