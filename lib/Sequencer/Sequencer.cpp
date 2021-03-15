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
    pinMode(19, INPUT);

    randomSeed(analogRead(19));

    pickNextHarmony();
  }

  void Sequencer::clockTick()
  {
    if ((clock->tickCounter) % (clock->clockDivider * 4) == 0)
    {
      pickNextHarmony();
    }

    Track *track;
    for (int trackInx = 0; trackInx < tracks->size(); trackInx++)
    {
      track = tracks->get(trackInx);
      track->clockTick(clock->tickCounter);
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
    if (currentScale == nullptr)
    {
      currentKey = static_cast<NoteType>(random(12));
      currentScale = &Scale::minor;
    }

    std::vector<Note> notes = currentScale->getNotes(currentKey, 0);
    currentKey = notes[3].type;

    seed++;
  }

  Note Sequencer::getNote(int inx, int octave)
  {
    return currentScale->getNote(currentKey, inx, octave);
  }
}