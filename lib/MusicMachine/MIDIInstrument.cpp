#include "MIDIInstrument.h"
#include <Arduino.h>
#include <MIDI.h>

#include "SerialMIDI.h"

namespace HLMusicMachine
{
  MIDIInstrument::MIDIInstrument(int channel, Scheduler *runner, int voiceCount, int port) : Instrument(runner, voiceCount)
  {
    this->channel = channel;
    this->port = port;
  }

  void MIDIInstrument::noteOn(int note, int vel, uint8_t voiceIndex)
  {
    if (!isEnabled)
    {
      return;
    }
    // Serial.printf("noteOn %i\n", note);

#ifdef MIDI_INTERFACE
    // usbMIDI.sendNoteOn(note, vel, channel);
    // serialMIDI.ports[port]->sendNoteOn(note, vel, channel);
#endif
  }

  void MIDIInstrument::noteOff(int note = 0, uint8_t voiceIndex)
  {
    // if (!isEnabled)
    // {
    //   return;
    // }

    // Serial.printf("noteOff %i\n", note);

#ifdef MIDI_INTERFACE
    // usbMIDI.sendNoteOff(note, 0, channel);
    // serialMIDI.ports[port]->sendNoteOff(note, 0, channel);
#endif
  }

  void MIDIInstrument::randomize()
  {
#ifdef MIDI_INTERFACE
    // int program = random(0, 6);
    // Serial.printf("Program change %i\n", program);
    // usbMIDI.sendProgramChange(program, channel);
#endif
  }
}