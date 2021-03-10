#include "Clock.h"
#include <Arduino.h>

Clock::Clock(Scheduler *runner) : Task(1 * TASK_SECOND, TASK_FOREVER, runner, false)
{
}

bool Clock::Callback()
{
    setInterval(clockInterval);
    delegate->clockTick();
    tickCounter++;
}

void Clock::setBpm(float bpm)
{
    bpm = constrain(bpm, minBpm, maxBpm);

    this->bpm = bpm;
    this->clockInterval = 60 * 1000000 / bpm / this->clockDivider; // microseconds

    Serial.printf("Bpm is  %f\n", bpm);
}

float Clock::getBpm()
{
    return bpm;
}
