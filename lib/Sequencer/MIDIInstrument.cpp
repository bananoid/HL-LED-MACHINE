#include "MIDIInstrument.h"
#include <Arduino.h>

namespace HLSequencer
{
  MIDIInstrument::MIDIInstrument(int channel, Scheduler *runner) : Instrument(runner)
  {
    this->channel = channel;
  }

  void MIDIInstrument::noteOn(int note = 0, int vel = 127)
  {
    if (note == 0)
    {
      note = defaultNote;
    }

    Instrument::noteOn(note, vel);
#ifdef MIDI_INTERFACE
    usbMIDI.sendNoteOn(note, vel, channel);
#endif
  }

  void MIDIInstrument::noteOff(int note = 0)
  {
    if (note == 0)
    {
      note = defaultNote;
    }

    Instrument::noteOff(note);
#ifdef MIDI_INTERFACE
    usbMIDI.sendNoteOff(note, 0, channel);
#endif
  }
}