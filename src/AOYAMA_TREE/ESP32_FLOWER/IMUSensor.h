#pragma once

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

#include "AOYAMA_TREE/COMMON/config.h"
#include <TaskSchedulerDeclarations.h>

class IMUSensorDelegate
{
public:
  virtual void onIMUOrientationData(sensors_event_t *orientationData);
};

class IMUSensor : public Task
{
public:
  IMUSensor(Scheduler *runner, IMUSensorDelegate *delegate);

  void begin();
  void update();

  bool Callback();

  IMUSensorDelegate *delegate = nullptr;

  Adafruit_BNO055 bno;

  void printEvent(sensors_event_t *event);
};