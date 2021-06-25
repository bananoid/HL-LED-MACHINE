#pragma once
namespace MathUtils
{
  template <typename T>
  float scale(T x, T in_min, T in_max, T out_min, T out_max)
  {
    return (x - (T)in_min) * ((T)out_max - (T)out_min) / ((T)in_max - (T)in_min) + (T)out_min;
  }
}