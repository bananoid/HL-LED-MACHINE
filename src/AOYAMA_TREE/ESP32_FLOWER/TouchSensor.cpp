#include "TouchSensor.h"
#include <Arduino.h>

#define N_SENSORS 6

#define TOUCH_PIN_1 12
#define TOUCH_PIN_2 14
#define TOUCH_PIN_3 27
#define TOUCH_PIN_4 33
#define TOUCH_PIN_5 32
#define TOUCH_PIN_6 15

int touchPins[] = {
    TOUCH_PIN_1,
    TOUCH_PIN_2,
    TOUCH_PIN_3,
    TOUCH_PIN_4,
    TOUCH_PIN_5,
    TOUCH_PIN_6,
};

struct TouchThreshold
{
  float sigfiltered = 0;
  float thsFilter = 0;
  bool on = false;
};

TouchThreshold touchThresholds[N_SENSORS];

TouchSensor::TouchSensor(TouchSensorDelegate *delegate)
{
  for (int i = 0; i < N_SENSORS; i++)
  {
    pinMode(touchPins[i], INPUT);
  }
  this->delegate = delegate;
}

void TouchSensor::update()
{
  for (int i = 0; i < N_SENSORS; i++)
  // for (int i = 0; i < 1; i++)
  {

    int touch = touchRead(touchPins[i]);

    if (touch <= 0)
    {
      continue;
    }

    touchThresholds[i].sigfiltered += (touch - touchThresholds[i].sigfiltered) * 0.08;
    touchThresholds[i].thsFilter += (touch - touchThresholds[i].thsFilter) * 0.0006;

    // Serial.printf("%f %f \n", touchThresholds[i].sigfiltered, touchThresholds[i].thsFilter);

    if (touchThresholds[i].sigfiltered * 1.04 < touchThresholds[i].thsFilter)
    {
      // Serial.printf("TouchSensor %i [%i]: (%i) %i\n", i, touchPins[i], touch, random(99));
      delegate->touchSensorOnTouch(i);

      touchThresholds[i].on = true;
    }
    else
    {
      touchThresholds[i].on = false;
    }
  }
}
