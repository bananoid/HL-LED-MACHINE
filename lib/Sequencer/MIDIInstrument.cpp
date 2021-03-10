#include "MIDIInstrument.h"
#include <Arduino.h>

MIDIInstrument::MIDIInstrument(int channel, Scheduler *runner) : Instrument(runner)
{
  this->channel = channel;
}

void MIDIInstrument::noteOn(int note, int vel)
{
  Instrument::noteOn(note, vel);
#ifdef MIDI_INTERFACE
  usbMIDI.sendNoteOn(note, vel, channel);
#endif
}

void MIDIInstrument::noteOff(int note)
{
  Instrument::noteOff(note);
#ifdef MIDI_INTERFACE
  usbMIDI.sendNoteOff(note, 0, channel);
#endif
}