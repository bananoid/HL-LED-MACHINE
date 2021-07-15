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
    if (counter < 0)
    {
      return;
    }

    if (counter == 0)
    {
      lastStepInx = 0;
      onCounter = 1;
      lastStep.note = 0;
      lastTrigTime = 0;
    }

    int stepLenght = Clock::getQuntizedTimePulses(parameters.stepLenght);
    int retrigSize = parameters.retrig;
    bool retrigActive = retrigSize != 0;
    bool retrigLFOActive = retrigSize < 0;

    if (retrigLFOActive)
    {
      int rLFOVal = parameters.retrigLFO;
      auto rLFOlen = Clock::getQuntizedTimePulses(rLFOVal);
      float phase = (float)counter / (float)rLFOlen * TWO_PI;
      float rLFO = cosf(phase);
      rLFO = asinf(rLFO) / HALF_PI;
      retrigSize = map(rLFO, -1.f, 1.f, parameters.retrigMin, parameters.retrigMax);

      // Serial.printf("c:%i l:%i v:%i",
      //               counter, Clock::getQuntizedTimePulses(retrigSize), retrigSize);
    }

    retrigSize = Clock::getQuntizedTimePulses(retrigSize);

    if (!retrigActive)
    {
      if (counter % stepLenght != 0)
      {
        Serial.println();
        return;
      }
    }

    int stepInx = counter / stepLenght;
    bool newStep = false;
    if (lastStepInx != stepInx)
    {
      newStep = true;
      lastStepInx = stepInx;
      lastTrigTime = counter;
    }

    uint32_t trigCounter = counter - lastTrigTime;

    if (retrigActive)
    {
      if (trigCounter % retrigSize != 0)
      {
        Serial.println();
        return;
      }
    }

    lastTrigTime = counter;

    // Serial.printf("\tTrig\n");

    bool isOn = isEuclidean(stepInx);

    if (newStep)
    {
      lastStep.note = onCounter % parameters.events;
      onCounter++;
      onCounter = onCounter % parameters.steps;
    }

    if (isOn)
    {
      int noteLenght = stepLenght;
      if (retrigActive)
      {
        noteLenght = min(stepLenght, retrigSize);
      }

      // noteLenght = 3; // Parametrize

      int vel = parameters.velocityMax;
      if (parameters.velocityLFOEnabled)
      {
        int velSpeed = parameters.velocityLFOSpeed;
        int velLen = Clock::getQuntizedTimePulses(velSpeed);
        float phase = (float)counter / (float)velLen * TWO_PI;
        float vLFO = cosf(phase);
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

          auto midiNote = tracker->getNote(noteInx + parameters.noteOffset, parameters.octave);
          // int midiNote = note.getMIDINoteNumber();
          instrument->trigNote(midiNote, vel, noteLenght, noteInx);

          // Serial.printf("noteInx %i %f\n", noteInx);
        }
        else
        {
          int chordCount = parameters.chord == 1 ? 3 : 4;
          for (int i = 0; i < chordCount; i++)
          {
            auto midiNote = tracker->getNote(i * (2 * parameters.noteSpread) + noteInx + parameters.noteOffset, parameters.octave);
            // int midiNote = note.getMIDINoteNumber();
            instrument->trigNote(midiNote, vel, noteLenght, noteInx);
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