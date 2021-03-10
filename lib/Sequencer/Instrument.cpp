#include "Instrument.h"
#include <Arduino.h>

namespace HLSequencer
{
    Instrument::Instrument(Scheduler *runner) : Task(TASK_MILLISECOND * 100, TASK_FOREVER, runner, false)
    {
        disable();
    }

    bool Instrument::Callback()
    {
        noteOff(lastNote);
        disable();
    }

    void Instrument::toggleEnabled()
    {
        isEnabled = !isEnabled;
    }

    void Instrument::noteOn(int note, int vel)
    {
        if (autoRelease)
        {
            long trigTime = min(delegate->getClockTime() * 0.9, this->trigTime);
            restartDelayed(trigTime);
        }
    }
    void Instrument::noteOff(int note)
    {
    }
}