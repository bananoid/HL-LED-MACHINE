#include "Track.h"

namespace HLSequencer
{
  Track::Track(Sequencer *sequencer, Instrument *instrument)
  {
    this->sequencer = sequencer;
    this->instrument = instrument;
    instrument->delegate = sequencer;
    generator = new EuclideanSequence();
  }

  void Track::clockTick(int counter)
  {
    int retrigSize = retrig;

    if (retrig < 0)
    {
      // TODO: parametrize retrig LFO
      float rLFO = sinf(counter / 24.0f * TWO_PI * (1.0 / retrigLFO));
      rLFO = asinf(rLFO) / HALF_PI;
      retrigSize = map(rLFO, -1.f, 1.f, retrigLFOMin, retrigLFOMax);
      int triplet = retrigSize % 2 == 0 ? 1 : 3;
      retrigSize = triplet * powf(2, retrigSize / 2);
    }

    if ((counter) % (retrigSize > 0 ? retrigSize : stepLenght) != 0)
    {
      return;
    }

    int stepInx = counter / stepLenght;
    bool newStep = false;
    if (lastStepInx != stepInx)
    {
      newStep = true;
      lastStepInx = stepInx;
    }

    bool isOn = generator->isOn(stepInx);

    if (newStep)
    {
      lastStep.note = onCounter % generator->events;
      onCounter++;
      retrigCount = 0;
    }

    // Serial.printf("isOn %i %i %i\n", isOn, retrigCount, stepInx);
    if (isOn)
    {
      int velocity = (97.0f / stepLenght * counter) + 30;
      int noteLeght = retrigSize > 0 ? retrigSize : stepLenght;

      if (type == MELODY)
      {
        if (chord == 0)
        {
          Note note = sequencer->getNote((lastStep.note % noteCount) * noteSpread, octave);
          int midiNote = note.getMIDINoteNumber();
          instrument->trigNote(midiNote, velocity, noteLeght);
        }
        else
        {
          int chordCount = chord == 1 ? 3 : 4;
          for (int i = 0; i < chordCount; i++)
          {
            Note note = sequencer->getNote(i * 2, octave);
            int midiNote = note.getMIDINoteNumber();
            instrument->trigNote(midiNote, velocity, noteLeght);
          }
        }
      }
      else
      {
        int midiNote = percussionNote.getMIDINoteNumber();
        instrument->trigNote(midiNote, velocity, noteLeght);
      }

      retrigCount++;
    }
  }
}