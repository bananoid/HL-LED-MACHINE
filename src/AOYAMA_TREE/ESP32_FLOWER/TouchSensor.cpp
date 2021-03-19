#include "TouchSensor.h"
#include <Arduino.h>

#define N_SENSORS 3

#define TOUCH_PIN_1 13
#define TOUCH_PIN_2 12
#define TOUCH_PIN_3 14

int touchPins[] = {
    TOUCH_PIN_1,
    TOUCH_PIN_2,
    TOUCH_PIN_3

};

TouchSensor::TouchSensor()
{
}

void TouchSensor::update()
{
  for (int i = 0; i < N_SENSORS; i++)
  {
    touchReads[i] = touchRead(touchPins[i]);
    Serial.printf("TouchSensor %i [%i]: %i\n", i, touchPins[i], touchReads[i]);
  }
}
