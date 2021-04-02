#include "Sequencer.h"
#include <Arduino.h>

namespace HLMusicMachine
{
  Sequencer::Sequencer(Tracker *tracker, Instrument *instrument)
  {
    this->tracker = tracker;
    this->instrument = instrument;
    instrument->delegate = tracker;
  }

  bool Sequencer::isEuclidean(int inx, int steps, int events, int offset)
  {
    if (events == 0)
    {
      return false;
    }

    int x = (inx + steps * 2 - offset) % steps;
    float step = (float)steps / (float)events;
    float fMod = fmodf(x, step);

    if (floor(fMod) == 0)
    {
      return true;
    }
    return false;
  }

  bool Sequencer::isEuclidean(int stepInx)
  {
    return isEuclidean(stepInx, parameters.steps, parameters.events, parameters.offset);
  }

  void Sequencer::randomize()
  {
    parameters.steps = random(minParameters.steps, maxParameters.steps + 1);

    parameters.events = random(minParameters.events, maxParameters.events + 1);

    parameters.offset = random(minParameters.offset, maxParameters.offset + 1);

    parameters.stepLenght = random(minParameters.stepLenght, maxParameters.stepLenght + 1);

    parameters.noteCount = random(minParameters.noteCount, maxParameters.noteCount + 1);
  }

  void Sequencer::clockTick(int counter)
  {
    int retrigSize = parameters.retrig;

    int stepLenght = Clock::getQuntizedTimePulses(parameters.stepLenght);

    if (parameters.retrig < 0)
    {
      // TODO: parametrize retrig LFO
      float rLFO = sinf(counter / 24.0f * TWO_PI * (1.0 / parameters.retrigLFO));
      rLFO = asinf(rLFO) / HALF_PI;
      retrigSize = map(rLFO, -1.f, 1.f, parameters.retrigLFOMin, parameters.retrigLFOMax);
      retrigSize = Clock::getQuntizedTimePulses(retrigSize);
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

    bool isOn = isEuclidean(stepInx);

    if (parameters.fillFactor < 1)
    {
      float fillEvents = map(parameters.fillFactor, 0.0f, 1.0f, 0.0f, (float)parameters.steps);
      bool fillMask = isEuclidean(stepInx, parameters.steps, fillEvents, parameters.offset);
      isOn = isOn && fillMask;
    }

    if (newStep)
    {
      lastStep.note = onCounter % parameters.events;
      onCounter++;
    }

    // Serial.printf("isOn %i %i %i\n", isOn, retrigCount, stepInx);
    if (isOn)
    {
      int noteLeght = retrigSize > 0 ? retrigSize : stepLenght;

      int vel = parameters.velocity;
      if (vel == -1)
      {
        float vLFO = sinf(counter / 24.0f * TWO_PI * (1.0 / parameters.velocityLFO));
        vLFO = asinf(vLFO) / HALF_PI;
        vel = map(vLFO, -1.f, 1.f, parameters.velocityLFOMin, parameters.velocityLFOMax);
      }

      if (type == MELODY)
      {
        if (parameters.chord == 0) // Arpeggio
        {
          int noteInx = 0;

          if (parameters.arpeggioType == ArpeggioType_Eucledian)
          {
            noteInx = (lastStep.note % parameters.noteCount) * parameters.noteSpread;
          }
          else if (parameters.arpeggioType == ArpeggioType_LFO)
          {
            float phase = counter / 24.0f * (1.0 / parameters.arpeggioLFO);
            float aLFO = sinf(phase * TWO_PI);
            aLFO = asinf(aLFO) / HALF_PI;
            aLFO = map(aLFO, -1.f, 1.f, 0, parameters.noteCount);
            noteInx = round(aLFO);
            noteInx *= parameters.noteSpread;
          }

          Note note = tracker->getNote(noteInx, parameters.octave);
          int midiNote = note.getMIDINoteNumber();
          instrument->trigNote(midiNote, vel, noteLeght);

          // Serial.printf("noteInx %i %f\n", noteInx);
        }
        else
        {
          int chordCount = parameters.chord == 1 ? 3 : 4;
          for (int i = 0; i < chordCount; i++)
          {
            Note note = tracker->getNote(i * 2, parameters.octave);
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