#pragma once

#include <Arduino.h>

#include "config.h"
#include <TaskSchedulerDeclarations.h>

#include "Clock.h"

class Sequencer : public ClockDelegate
{
private:
public:
  Sequencer(Scheduler *runner);

  Clock *clock;
  void clockTick() override;
};
