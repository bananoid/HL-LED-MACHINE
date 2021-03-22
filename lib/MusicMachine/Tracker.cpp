#include "Tracker.h"

namespace HLMusicMachine
{
  Tracker::Tracker(Scheduler *runner)
  {
    clock = new Clock(runner);
    clock->delegate = this;
    clock->play();

    tracks = new LinkedList<Track *>();

    pinMode(19, INPUT);

    randomSeed(analogRead(19));

    pickNextHarmony();
  }

  void Tracker::clockTick()
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

  long Tracker::getClockTime()
  {
    return clock->clockInterval;
  }

  void Tracker::appendTrack(Track *track)
  {
    tracks->add(track);
  }

  void Tracker::pickNextHarmony()
  {
    if (currentScale == nullptr)
    {
      currentScale = const_cast<Scale *>(&Scale::major);
      // currentScale = &Scale::minor;
      // currentKey = static_cast<NoteType>(random(12));
      currentKey = C;
    }
    else
    {
      std::vector<Note> notes = currentScale->getNotes(currentKey, 0);
      for (Note note : notes)
      {
        Serial.print("[ ");
        Note::printNoteType(note.type);
        Serial.print(" ]");
      }
      Serial.print("\n");

      if (harmonyCounter % 16 == 0)
      {
        progressionInterval = random(0, 6);
        Serial.printf("change progressionInterval %i \n", progressionInterval);

        // if (progressionIntervalCounter % 2 == 0)
        // {
        //   currentScale = &Scale::major;
        //   Serial.println("Major");
        // }
        // else
        // {
        //   currentScale = &Scale::minor;
        //   Serial.println("Minor");
        // }

        progressionIntervalCounter++;
      }

      currentKey = notes[progressionInterval].type;
    }

    // currentScale = random(4) == 0 ? &Scale::minor : &Scale::major;

    Note::printNoteType(currentKey);
    Serial.printf(" key %i\n", currentKey);

    harmonyCounter++;
  }

  Note Tracker::getNote(int inx, int octave)
  {
    return currentScale->getNote(currentKey, inx, octave);
  }
}