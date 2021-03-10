#pragma once
#include <Arduino.h>

struct EuclideanSequence
{
  int steps = 16;
  const int maxSteps = 16;
  const int minSteps = 0;

  int events = 4;
  const int maxEvents = 16;
  const int minEvents = 0;

  int offset = 0;
  const int maxOffset = 16;
  const int minOffset = 0;

  bool isOn(int index);

  bool isOn(int index)
  {
    if (events == 0)
    {
      return false;
    }
    int x = (index + steps * 2 - offset) % steps;
    float step = (float)steps / (float)events;
    float fMod = fmodf(x, step);

    return floor(fMod) == 0;
  }
};
