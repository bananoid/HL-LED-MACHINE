#pragma once
#include <Arduino.h>

#define N_TOUCH_SENSORS 6
#define N_CROWN_TOUCH_SENSORS 5

#define TOUCH_PIN_1 12
#define TOUCH_PIN_2 14
#define TOUCH_PIN_3 27
#define TOUCH_PIN_4 33
#define TOUCH_PIN_5 32
#define TOUCH_PIN_6 15

struct TouchSensorState
{
  float sigfiltered = 0;
  float thsFilter = 0;
  bool on = false;
};

class TouchSensorDelegate
{
public:
  virtual void touchSensorOnTouch(int touchId);
};

class TouchSensor
{
public:
  TouchSensor(TouchSensorDelegate *delegate);

  TouchSensorDelegate *delegate = nullptr;
  int touchPins[N_TOUCH_SENSORS] = {
      TOUCH_PIN_1,
      TOUCH_PIN_2,
      TOUCH_PIN_3,
      TOUCH_PIN_4,
      TOUCH_PIN_5,
      TOUCH_PIN_6

  };

  TouchSensorState states[N_TOUCH_SENSORS];

  void update();

  int getCrownOnTouches();
};
