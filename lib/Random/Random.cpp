#pragma once
#include "Random.h"

float Random::fract(float x)
{
  return x - ((int)x);
}

float Random::rnd(float x)
{
  return fract((sinf(x) * 0.5 + 0.5) * 1e4);
}