#include "Sequencer.h"

namespace HLSequencer
{
  Sequencer::Sequencer(Scheduler *runner)
  {
    clock = new Clock(runner);
    clock->delegate = this;
    clock->play();

    tracks = new LinkedList<Track *>();

    pinMode(13, OUTPUT);
  }

  void Sequencer::clockTick()
  {

    if ((clock->tickCounter) % (clock->clockDivider * 4 * 4) == 0)
    {
      pickNextHarmony();
    }

    Track *track;
    for (int trackInx = 0; trackInx < tracks->size(); trackInx++)
    {
      if ((clock->tickCounter) % 6 == 0)
      {
        track = tracks->get(trackInx);
        int timeInx = clock->tickCounter / 6;
        Step *step = track->sequences->get(0)->isOn(timeInx);

        if (step)
        {
          int note = currentScale->getMidiNote(currentKey, step->note);
          // Serial.printf("%i %i\n", timeInx, step->note);
          digitalWrite(13, true);
          track->instrument->noteOn(note);
        }
        else
        {
          digitalWrite(13, false);
        }
      }
    }
  }

  long Sequencer::getClockTime()
  {
    return clock->clockInterval;
  }

  void Sequencer::appendTrack(Track *track)
  {
    tracks->add(track);
  }

  void Sequencer::pickNextHarmony()
  {
    currentScale = random(1) == 0 ? &MusicTheory::Scale::minor : &MusicTheory::Scale::major;
    currentKey = static_cast<MusicTheory::NoteType>(random(12));
    seed++;

    Serial.println("pickNextHarmony");
  }
}