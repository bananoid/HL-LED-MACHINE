#include "Scale.hpp"
#include <Arduino.h>

namespace MusicTheory
{

  Scale::Scale(Interval *intervals, int length)
  {
    this->length = length;
    this->intervals.assign(intervals, intervals + length);
  }

  std::vector<Note> Scale::getNotes(NoteType key, int octave)
  {
    std::vector<Note> notes;
    notes.reserve(this->intervals.size());

    Note root = Note(key, octave);
    for (Interval current : intervals)
    {
      notes.push_back(root + current);
    }

    return notes;
  }

  Note Scale::getNote(NoteType key, int noteInx, int octave)
  {
    int intervalSize = this->intervals.size();
    int inx = noteInx % intervalSize;
    octave += noteInx / intervalSize;
    Note root = Note(key, octave);
    Interval current = this->intervals[inx];
    Note note = root + current;

    // Serial.printf("intSize %i octave %i inx %i interval %i\n", intervalSize, octave, inx, current);

    return note;
  }

  Interval majorIntervals[] = {Interval::P1, Interval::M2, Interval::M3, Interval::P4, Interval::P5, Interval::M6, Interval::M7};
  const Scale Scale::major = Scale(majorIntervals, 7);
  Interval minorIntervals[] = {Interval::P1, Interval::M2, Interval::m3, Interval::P4, Interval::P5, Interval::m6, Interval::m7};
  const Scale Scale::minor = Scale(minorIntervals, 7);
}
