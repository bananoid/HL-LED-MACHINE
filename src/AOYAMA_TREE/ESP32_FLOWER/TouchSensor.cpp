#include "TouchSensor.h"

TouchSensor::TouchSensor(TouchSensorDelegate *delegate)
{
  for (int i = 0; i < N_TOUCH_SENSORS; i++)
  {
    pinMode(touchPins[i], INPUT);
  }
  this->delegate = delegate;
}

void TouchSensor::update()
{
  for (int i = 0; i < N_TOUCH_SENSORS; i++)
  // for (int i = 0; i < 1; i++)
  {

    int touch = touchRead(touchPins[i]);

    if (touch <= 0)
    {
      continue;
    }

    states[i].sigfiltered += (touch - states[i].sigfiltered) * 0.08;
    states[i].thsFilter += (touch - states[i].thsFilter) * 0.0006;

    // Serial.printf("%f %f \n", states[i].sigfiltered, states[i].thsFilter);

    if (states[i].sigfiltered * 1.04 < states[i].thsFilter)
    {
      // Serial.printf("TouchSensor %i [%i]: (%i) %i\n", i, touchPins[i], touch, random(99));
      delegate->touchSensorOnTouch(i);

      states[i].on = true;
    }
    else
    {
      states[i].on = false;
    }
  }
}

int TouchSensor::getCrownOnTouches()
{
  int count = 0;
  for (uint8_t i = 0; i < N_CROWN_TOUCH_SENSORS; i++)
  {
    if (states[i].on)
    {
      count++;
    }
  }
  return count;
}