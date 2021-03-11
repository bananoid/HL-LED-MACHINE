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
        return false;
    }

    void Instrument::toggleEnabled()
    {
        isEnabled = !isEnabled;
    }

    void Instrument::noteOn(int note, int vel, int autoReleaseLength)
    {
        if (lastNote != -1)
        {
            noteOff(lastNote);
        }

        lastNote = note;

        if (autoReleaseLength != 0)
        {
            long trigTime;
            if (autoReleaseLength > 0)
            {
                trigTime = delegate->getClockTime() * autoReleaseLength;
            }
            else
            {
                trigTime = this->trigTime;
                trigTime = min(delegate->getClockTime() * 0.5, trigTime);
            }
            restartDelayed(trigTime);
        }
    }
    void Instrument::noteOff(int note)
    {
        lastNote = -1;
    }
}