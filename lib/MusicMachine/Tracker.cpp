#include "Tracker.h"

namespace HLMusicMachine
{
  Tracker::Tracker(Scheduler *runner)
  {
    this->runner = runner;
    clock = masterClock;
    clock->begin();
    clock->delegate = this;
    // clock->play();

    // pinMode(19, INPUT);

    // randomSeed(analogRead(19));

    pickNextHarmony();
    // currentScale = const_cast<Scale *>(&Scale::minor);
    // currentKey = C;
  }

  void Tracker::appendTrack(Track *track)
  {
    tracks.push_back(track);
  }

  void Tracker::clockTick()
  {
    // if ((clock->tickCounter) % (clock->clockDivider * 32) == 0)
    if ((clock->tickCounter) % (clock->clockDivider * 8) == 0)
    {
      // pickNextHarmony();
    }

    if ((clock->tickCounter) % (clock->clockDivider * 1) == 0)
    {
      if (delegate != nullptr)
      {
        delegate->trackerBarTick();
      }
    }

    for (Track *track : tracks)
    {
      track->clockTick(clock->tickCounter);
    }
  }

  long Tracker::getClockTime()
  {
    return clock->clockInterval;
  }

  void Tracker::pickNextHarmony()
  {
    if (currentScale == nullptr)
    {
      // currentScale = const_cast<Scale *>(&Scale::major);
      currentScale = const_cast<Scale *>(&Scale::minorPentatonic);
      // currentKey = static_cast<NoteType>(random(12));
      currentKey = C;
    }
    else
    {
      std::vector<Note> notes = currentScale->getNotes(currentKey, 0);
      // for (Note note : notes)
      // {
      //   Serial.print("[ ");
      //   Note::printNoteType(note.type);
      //   Serial.print(" ]");
      // }
      // Serial.print("\n");

      if (harmonyCounter % 16 == 0)
      {
        progressionInterval = random(0, 6);
        // Serial.printf("change progressionInterval %i \n", progressionInterval);

        // if (progressionIntervalCounter % 2 == 0)
        // {
        //   currentScale = const_cast<Scale *>(&Scale::major);
        //   Serial.println("Major");
        // }
        // else
        // {
        //   currentScale = const_cast<Scale *>(&Scale::minor);
        //   Serial.println("Minor");
        // }

        progressionIntervalCounter++;
      }

      // currentKey = notes[progressionInterval].type;
    }

    // currentScale = harmonyCounter % 2 == 0 ? &Scale::minorPentatonic : &Scale::majorPentatonic;

    // Note::printNoteType(currentKey);
    // Serial.printf(" key %i\n", harmonyCounter);

    harmonyCounter++;
  }

  Note Tracker::getNote(int inx, int octave)
  {
    return currentScale->getNote(currentKey, inx, octave);
  }

  void Tracker::setScaleIndex(int i)
  {
    scaleIndex = i;

    switch (scaleIndex)
    {
    case 0:
      currentScale = const_cast<Scale *>(&Scale::minorPentatonic);
      break;
    case 1:
      currentScale = const_cast<Scale *>(&Scale::majorPentatonic);
      break;
    case 2:
      currentScale = const_cast<Scale *>(&Scale::custom1);
      break;
    case 3:
      currentScale = const_cast<Scale *>(&Scale::custom2);
      break;
    }
  }
  void Tracker::setKeyIndex(int i)
  {
    keyIndex = i;
    switch (keyIndex)
    {
    case 0:
      currentKey = C;
      break;
    case 1:
      currentKey = EFlat;
      break;
    case 2:
      currentKey = A;
      break;
    case 3:
      currentKey = GFlat;
      break;
    }
  }
}
