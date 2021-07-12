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
    return isEuclidean(stepInx,
                       parameters.steps,
                       parameters.events,
                       parameters.offset);
  }

  void Sequencer::randomize()
  {
    // parameters.steps = random(minParameters.steps, maxParameters.steps + 1);

    // parameters.events = random(minParameters.events, maxParameters.events + 1);

    // parameters.offset = random(minParameters.offset, maxParameters.offset + 1);

    // parameters.stepLenght = random(minParameters.stepLenght, maxParameters.stepLenght + 1);

    // parameters.noteCount = random(minParameters.noteCount, maxParameters.noteCount + 1);
  }

  void Sequencer::clockTick(int counter)
  {
    // float pbLFO = sinf(3 * counter / 24.0f * TWO_PI * (1.0 / parameters.velocityLFO));
    // instrument->pitchBend(pbLFO);

    if (counter == 0)
    {
      lastStepInx = 0;
      onCounter = 0;
    }

    int retrigSize = parameters.retrig;

    int stepLenght = Clock::getQuntizedTimePulses(parameters.stepLenght);

    if (parameters.retrig < 0)
    {
      // TODO: parametrize retrig LFO
      float rLFO = sinf(counter / 24.0f * TWO_PI * (1.0 / parameters.retrigLFO));
      rLFO = asinf(rLFO) / HALF_PI;
      retrigSize = map(rLFO, -1.f, 1.f, parameters.retrigLFO.min, parameters.retrigLFO.max);
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

    if (newStep)
    {
      lastStep.note = onCounter % parameters.events;
      onCounter++;
    }

    // Serial.printf("isOn %i %i %i\n", isOn, retrigCount, stepInx);
    if (isOn)
    {
      int noteLenght = retrigSize > 0 ? retrigSize : stepLenght;
      if (retrigSize > 0)
      {
        noteLenght = min(stepLenght, retrigSize);
      }

      int vel = parameters.velocityMax;
      if (parameters.velocityLFOEnabled)
      {
        float vLFO = sinf(counter / 24.0f * TWO_PI * (1.0 / parameters.velocityLFOSpeed));
        vLFO = asinf(vLFO) / HALF_PI;
        vel = map(vLFO, -1.f, 1.f, parameters.velocityMin, parameters.velocityMax);
      }

      if (type == MELODY)
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

        if (!parameters.chord) // Arpeggio
        {

          Note note = tracker->getNote(noteInx + parameters.noteOffset, parameters.octave);
          int midiNote = note.getMIDINoteNumber();
          instrument->trigNote(midiNote, vel, noteLenght);

          // Serial.printf("noteInx %i %f\n", noteInx);
        }
        else
        {
          int chordCount = parameters.chord == 1 ? 3 : 4;
          for (int i = 0; i < chordCount; i++)
          {
            Note note = tracker->getNote(i * (2 * parameters.noteSpread) + noteInx + parameters.noteOffset, parameters.octave);
            int midiNote = note.getMIDINoteNumber();
            instrument->trigNote(midiNote, vel, noteLenght);
          }
        }
      }
      else
      {
        int midiNote = percussionNote.getMIDINoteNumber();
        instrument->trigNote(midiNote, vel, noteLenght);
      }
    }
  }
}