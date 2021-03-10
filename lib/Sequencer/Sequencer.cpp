#include "Sequencer.h"

Sequencer::Sequencer(Scheduler *runner)
{
  clock = new Clock(runner);
  clock->delegate = this;
  clock->play();

  pinMode(13, OUTPUT);
}

void Sequencer::clockTick()
{

  if ((clock->tickCounter) % 24 == 0)
  {
    Serial.printf("clockTick %i  %i\n", clock->clockInterval, clock->tickCounter);
    digitalWrite(13, true);
  }
  if ((clock->tickCounter - 12) % 24 == 0)
  {
    digitalWrite(13, false);
  }
}