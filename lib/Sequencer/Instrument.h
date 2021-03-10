#pragma once

#include "config.h"
// #define _TASK_TIMEOUT
#include <TaskSchedulerDeclarations.h>

namespace HLSequencer
{
    class InstrumentDelegate
    {
    public:
        // virtual void clockTick(); // virtual because it is not implemented in the class
        virtual long getClockTime();
    };

    class Instrument : public Task
    {
    public:
        Instrument(Scheduler *runner);
        InstrumentDelegate *delegate;

        bool Callback();

        const int minTrigTime = 1 * TASK_MILLISECOND;
        const int maxTrigTime = 100 * TASK_MILLISECOND;
        long trigTime = TASK_MILLISECOND * 30;
        bool autoRelease = true;

        bool isEnabled = false;
        void toggleEnabled();

        int lastNote;
        int defaultNote = 36; // Kick
        virtual void noteOn(int note = 0, int vel = 127);
        virtual void noteOff(int note = 0);
    };
}