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
      float rLFO = sinf(counter * 0.001);
      rLFO = asinf(rLFO) / HALF_PI;
      retrigSize = map(rLFO, -1.f, 1.f, 0.f, 4.f);
      retrigSize = 3 * powf(2, retrigSize);
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

    Serial.printf("isOn %i %i %i\n", isOn, retrigCount, stepInx);
    if (isOn)
    {
      Note note = sequencer->getNote((lastStep.note % noteCount) * noteSpread, octave);
      int midiNote = note.getMIDINoteNumber();

      // TODO: velocity modulation
      int velocity = (97.0f / stepLenght * counter) + 30;
      // int velocity = 127;

      int noteLeght = retrigSize > 0 ? retrigSize : stepLenght;

      instrument->noteOn(midiNote, velocity, noteLeght);

      retrigCount++;
    }
  }
}