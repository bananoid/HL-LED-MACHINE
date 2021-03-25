#pragma once

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

#include "AOYAMA_TREE/COMMON/config.h"

class IMUSensorDelegate
{
public:
  virtual void onIMUOrientationData(sensors_event_t *orientationData);
};

class IMUSensor
{
public:
  IMUSensor(IMUSensorDelegate *delegate);

  void begin();
  void update();

  IMUSensorDelegate *delegate = nullptr;

  Adafruit_BNO055 bno;

  void printEvent(sensors_event_t *event);
};
