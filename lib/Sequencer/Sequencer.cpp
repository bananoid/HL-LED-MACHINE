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
    if ((clock->tickCounter) % (clock->clockDivider * 4 * 4) == 0)
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
    // TODO: pick next scale from prev chord

    // currentScale = random(1) == 0 ? &MusicTheory::Scale::minor : &MusicTheory::Scale::major;
    currentScale = &MusicTheory::Scale::minor;
    currentKey = static_cast<MusicTheory::NoteType>(random(12));
    seed++;

    std::vector<MusicTheory::Note> notes = currentScale->getNotes(currentKey, 1);
  }

  Note Sequencer::getNote(int inx, int octave)
  {
    return currentScale->getNote(currentKey, inx, octave);
  }
}