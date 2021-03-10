#pragma once

#include "config.h"
// #define _TASK_TIMEOUT
#include <TaskSchedulerDeclarations.h>

class InstrumentDelegate
{
public:
    // virtual void clockTick(); // virtual because it is not implemented in the class
    virtual long getClockTime();
};

class Instrument : public Task
{
private:
    /* data */
public:
    Instrument(int pin, Scheduler *runner);

    InstrumentDelegate *delegate;

    bool Callback();

    void trig(bool on);
    bool isEuclidianSeq(int index);

    int pin;

    int frequency = 100;
    const int maxFrequency = 1000;
    const int minFrequency = 20;

    int steps = 16;
    const int maxSteps = 16;
    const int minSteps = 0;

    int events = 4;
    const int maxEvents = 16;
    const int minEvents = 0;

    int offset = 0;
    const int maxOffset = 16;
    const int minOffset = 0;

    const int minTrigTime = 1 * TASK_MILLISECOND;
    const int maxTrigTime = 100 * TASK_MILLISECOND;
    long trigTime = TASK_MILLISECOND * 30;
    
    const int minTrigPWM = 150;
    const int maxTrigPWM = 255;
    int trigPWM = 255;

    bool isPlaying = false;
    void togglePlayPause();
};
