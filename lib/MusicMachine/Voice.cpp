#include "Instrument.h"
#include <Arduino.h>

namespace HLMusicMachine
{
  Voice::Voice(Scheduler *runner) // : Task(TASK_MILLISECOND * 100, TASK_FOREVER, runner, false)
  {
    voiceTask.set(TASK_MILLISECOND * 100, TASK_FOREVER, [this]() {
      noteOff(lastNote);
      voiceTask.disable();
    });
    runner->addTask(voiceTask);
    voiceTask.disable();
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
      delegate->noteOn(note, vel, index);

      long noteTime;

      if (trigTime > 0)
      {
        noteTime = trigTime;
      }
      else
      {
        noteTime = delegate->getClockTime() * noteLenght;
      }

      voiceTask.restartDelayed(noteTime);

      // Serial.printf("noteLenght %i %i \n", noteLenght, noteTime);
    }
  }
  void Voice::noteOff(int note)
  {
    delegate->noteOff(note, index);
    // lastNote = -1;
  }
}