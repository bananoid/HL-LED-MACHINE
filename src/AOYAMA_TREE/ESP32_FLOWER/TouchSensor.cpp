#include "TouchSensor.h"
#include <Arduino.h>

#define N_SENSORS 5

#define TOUCH_PIN_1 12
#define TOUCH_PIN_2 14
#define TOUCH_PIN_3 27
#define TOUCH_PIN_4 33
#define TOUCH_PIN_5 32

int touchPins[] = {
    TOUCH_PIN_1,
    TOUCH_PIN_2,
    TOUCH_PIN_3,
    TOUCH_PIN_4,
    TOUCH_PIN_5,
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
