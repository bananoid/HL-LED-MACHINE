#include "Track.h"

namespace HLSequencer
{
  Track::Track(Tracker *tracker, Instrument *instrument)
  {
    this->tracker = tracker;
    this->instrument = instrument;
    instrument->delegate = tracker;
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
    }

    // Serial.printf("isOn %i %i %i\n", isOn, retrigCount, stepInx);
    if (isOn)
    {
      int noteLeght = retrigSize > 0 ? retrigSize : stepLenght;

      int vel = velocity;
      if (vel == -1)
      {
        float vLFO = sinf(counter / 24.0f * TWO_PI * (1.0 / velocityLFO));
        vLFO = asinf(vLFO) / HALF_PI;
        vel = map(vLFO, -1.f, 1.f, velocityLFOMin, velocityLFOMax);
      }

      if (type == MELODY)
      {
        if (chord == 0) // Arpeggio
        {
          int noteInx = 0;

          if (arpeggioType == ArpeggioType_Eucledian)
          {
            noteInx = (lastStep.note % noteCount) * noteSpread;
          }
          else if (arpeggioType == ArpeggioType_LFO)
          {
            float phase = counter / 24.0f * (1.0 / arpeggioLFO);
            float aLFO = sinf(phase * TWO_PI);
            aLFO = asinf(aLFO) / HALF_PI;
            aLFO = map(aLFO, -1.f, 1.f, 0, noteCount);
            noteInx = round(aLFO);
            noteInx *= noteSpread;
          }

          Note note = tracker->getNote(noteInx, octave);
          int midiNote = note.getMIDINoteNumber();
          instrument->trigNote(midiNote, vel, noteLeght);

          // Serial.printf("noteInx %i %f\n", noteInx);
        }
        else
        {
          int chordCount = chord == 1 ? 3 : 4;
          for (int i = 0; i < chordCount; i++)
          {
            Note note = tracker->getNote(i * 2, octave);
            int midiNote = note.getMIDINoteNumber();
            instrument->trigNote(midiNote, vel, noteLeght);
          }
        }
      }
      else
      {
        int midiNote = percussionNote.getMIDINoteNumber();
        instrument->trigNote(midiNote, vel, noteLeght);
      }
    }
  }
}