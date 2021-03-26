#include "config.h"

#define ARDUINO_ARCH_ESP32 // This is to make TaskScheduler _TASK_STD_FUNCTION work on teensy
#define _TASK_STD_FUNCTION
#include <TaskScheduler.h>
#include "LedSynth.h"

Scheduler runner;
LedSynth *ledSynth;

void setup()
{
  ledSynth = new LedSynth();
  ledSynth->begin(&runner);
}

void loop()
{
  runner.execute();

  ledSynth->screen->sayHello(2);
  ledSynth->update();
}
