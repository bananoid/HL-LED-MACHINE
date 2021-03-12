#include "Sequencer.h"

using namespace MusicTheory;

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
    int gridSize = 6 * 4;
    int retrigSize = 6;
    bool retrig = true;

    float oscA = sinf(clock->tickCounter * 0.012442);
    oscA = asinf(oscA) / HALF_PI;
    retrigSize = map(oscA, -1.f, 1.f, 1.f, 24.f);

    if ((clock->tickCounter) % (clock->clockDivider * 4 * 4) == 0)
    {
      pickNextHarmony();
    }

    Track *track;
    for (int trackInx = 0; trackInx < tracks->size(); trackInx++)
    {
      if ((clock->tickCounter) % (retrig ? retrigSize : gridSize) == 0)
      {
        int timeInx = clock->tickCounter / gridSize;

        track = tracks->get(trackInx);
        SequenceGenerator *generator = track->sequences->get(0);

        bool isOn = generator->isOn(timeInx);
        Step *step = &generator->lastStep;

        if (isOn || retrig)
        {
          MusicTheory::Note note = currentScale->getNote(currentKey, (step->note % 4) * 3, 3);
          int midiNote = note.getMIDINoteNumber();
          track->instrument->noteOn(midiNote, (timeInx % 4) * 40 + 30, 100);
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

    std::vector<MusicTheory::Note> notes = currentScale->getNotes(currentKey, 1);
  }
}