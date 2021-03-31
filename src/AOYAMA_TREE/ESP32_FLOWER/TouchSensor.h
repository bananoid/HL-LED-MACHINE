#pragma once

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

  void update();

  int touchReads[];
};