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
    if (!isEnabled)
    {
      return;
    }
    // Serial.printf("noteOn %i\n", note);

#ifdef MIDI_INTERFACE
    usbMIDI.sendNoteOn(note, vel, channel);
#endif
  }

  void MIDIInstrument::noteOff(int note = 0)
  {
    // if (!isEnabled)
    // {
    //   return;
    // }

    // Serial.printf("noteOff %i\n", note);

#ifdef MIDI_INTERFACE
    usbMIDI.sendNoteOff(note, 0, channel);
#endif
  }

  void MIDIInstrument::randomize()
  {
#ifdef MIDI_INTERFACE
    int program = random(0, 6);
    // Serial.printf("Program change %i\n", program);
    usbMIDI.sendProgramChange(program, channel);
#endif
  }
}