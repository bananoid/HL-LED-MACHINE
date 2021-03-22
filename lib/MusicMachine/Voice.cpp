#include "Instrument.h"
#include <Arduino.h>

namespace HLSequencer
{
  Voice::Voice(Scheduler *runner) : Task(TASK_MILLISECOND * 100, TASK_FOREVER, runner, false)
  {
    disable();
  }

  bool Voice::Callback()
  {
    noteOff(lastNote);
    disable();
    return false;
  }

  void Voice::noteOn(int note, int vel, int noteLenght)
  {
    if (lastNote != -1)
    {
      noteOff(lastNote);
    }

    lastNote = note;

    if (noteLenght != 0)
    {
      delegate->noteOn(note, vel);

      long noteTime;

      if (trigTime > 0)
      {
        noteTime = trigTime;
      }
      else
      {
        delegate->getClockTime() * noteLenght;
      }

      restartDelayed(noteTime);

      // Serial.printf("noteLenght %i %i \n", noteLenght, noteTime);
    }
  }
  void Voice::noteOff(int note)
  {
    delegate->noteOff(note);
    // lastNote = -1;
  }
}