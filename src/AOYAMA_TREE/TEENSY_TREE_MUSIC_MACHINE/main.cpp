#include "config.h"
#include "MusicMachine.h"
#include <TaskScheduler.h>

Scheduler runner;
MusicMachine *musicMachine;

void setup()
{
  musicMachine = new MusicMachine(&runner);
}

void loop()
{
  musicMachine->update();
  runner.execute();
}
