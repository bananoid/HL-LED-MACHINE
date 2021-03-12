#include "MIDIInstrument.h"
#include <Arduino.h>

namespace HLSequencer
{
  MIDIInstrument::MIDIInstrument(int channel, Scheduler *runner) : Instrument(runner)
  {
    this->channel = channel;
  }

  void MIDIInstrument::noteOn(int note, int vel, int autoReleaseLength)
  {
    Instrument::noteOn(note, vel, autoReleaseLength);
    // Serial.printf("noteOn %i\n", note);

#ifdef MIDI_INTERFACE
    usbMIDI.sendNoteOn(note, vel, channel);
#endif
  }

  void MIDIInstrument::noteOff(int note = 0)
  {
    Instrument::noteOff(note);
    // Serial.printf("noteOff %i\n", note);

#ifdef MIDI_INTERFACE
    usbMIDI.sendNoteOff(note, 0, channel);
#endif
  }
}