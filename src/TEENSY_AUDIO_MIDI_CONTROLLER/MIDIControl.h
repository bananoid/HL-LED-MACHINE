#ifndef HL_SRC_TEENSY_AUDIO_MIDI_CONTROLLER_MIDICONTROL_MIDICONTROL
#define HL_SRC_TEENSY_AUDIO_MIDI_CONTROLLER_MIDICONTROL_MIDICONTROL

#include <ControlMessages.h>
#include <LEDSyntMessages.h>

class MIDIControlDelegate
{
public:
  virtual void midiControlReceiveMsg(ControlMsg *message);
};

class MIDIControl
{
private:
public:
  MIDIControlDelegate *delegate;
  void begin();
  void update();
};
#endif /* HL_SRC_TEENSY_AUDIO_MIDI_CONTROLLER_MIDICONTROL_MIDICONTROL */
