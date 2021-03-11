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

    Track *track;
    for (int trackInx = 0; trackInx < tracks->size(); trackInx++)
    {
      if ((clock->tickCounter) % 6 == 0)
      {
        track = tracks->get(trackInx);
        int timeInx = clock->tickCounter / 6;
        int noteIndex = track->sequences->get(0)->isOn(timeInx);

        Serial.printf("%i %i\n", timeInx, noteIndex);
        if (noteIndex > 0)
        {
          digitalWrite(13, true);
          track->instrument->noteOn();
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
}