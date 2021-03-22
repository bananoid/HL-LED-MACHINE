#include "MIDIInstrument.h"
#include <Arduino.h>

namespace HLMusicMachine
{
  MIDIInstrument::MIDIInstrument(int channel, Scheduler *runner, int voiceCount) : Instrument(runner, voiceCount)
  {
    this->channel = channel;
  }

  void MIDIInstrument::noteOn(int note, int vel)
  {
    // Serial.printf("noteOn %i\n", note);

#ifdef MIDI_INTERFACE
    usbMIDI.sendNoteOn(note, vel, channel);
#endif
  }

  void MIDIInstrument::noteOff(int note = 0)
  {
    // Serial.printf("noteOff %i\n", note);

#ifdef MIDI_INTERFACE
    usbMIDI.sendNoteOff(note, 0, channel);
#endif
  }
}