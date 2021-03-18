#pragma once

#include <MPU9250_asukiaaa.h>

class GyroSensor
{
public:
  void begin();

  void update();

  MPU9250_asukiaaa mySensor;
  float aX, aY, aZ, aSqrt, gX, gY, gZ, mDirection, mX, mY, mZ;
};
