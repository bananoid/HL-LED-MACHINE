#pragma once

#include <MathUtils.h>
#include <iostream>

namespace HLMusicMachine
{
  template <typename T>
  struct Parameter
  {
  private:
    float value;

  public:
    T min;
    T max;

    Parameter(T value, T min, T max)
    {
      this->value = value;
      this->min = min;
      this->max = max;
    }

    inline Parameter operator=(T v)
    {
      value = v;
      return *this;
    }

    inline operator T() const
    {
      return (T)value;
    }

    Parameter &operator+=(const float inc)
    {
      if (min < max)
      {
        value = constrain(value + inc, (float)min, (float)max);
      }
      else
      {
        value = constrain(value + inc, (float)max, (float)min);
      }
      return *this;
    }

    float scale(float a, float b)
    {
      return MathUtils::scale((float)value, (float)min, (float)max, (float)a, (float)b);
    }

    void setValue(float v, float from, float to)
    {
      value = MathUtils::scale((float)v, (float)from, (float)to, (float)min, (float)max);
    }

    std::ostream &operator<<(std::ostream &os)
    {
      // T v = (T)value;
      return os << value;
    }

    // std::istream &operator>>(std::istream &os)
    // {
    //   os >> value;

    //   return os;
    // }
  };

  template <typename T>
  std::istream &operator>>(std::istream &os, const Parameter<T> p)
  {
    os >> p;

    return os;
  }
}