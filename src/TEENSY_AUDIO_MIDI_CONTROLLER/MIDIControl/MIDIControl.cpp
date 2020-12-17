#include "MIDIControl.h"

#include <USBHost_t36.h> // access to USB MIDI devices (plugged into 2nd USB port)

// USB Host MIDI
USBHost myusb;
USBHub hub1(myusb);
USBHub hub2(myusb);
MIDIDevice midi1(myusb);

void MIDIControl::begin()
{
  myusb.begin();
}

void MIDIControl::update()
{
  if (!delegate)
  {
    return;
  }

  while (midi1.read())
  {

    MIDIDeviceBase::MidiType type = (MIDIDeviceBase::MidiType)midi1.getType();
    uint8_t channel = midi1.getChannel();

    if (type == MIDIDeviceBase::MidiType::NoteOn)
    {
      ControlButtonPress msg;
      msg.type = LEDSynthMessages::CONTROL_BUTTON_PRESS_MSG;
      msg.channel = channel;
      msg.id = midi1.getData1();

      delegate->midiControlReceiveMsg((ControlMsg *)&msg);
    }
    else if (type == MIDIDeviceBase::MidiType::NoteOff)
    {
      ControlButtonRelease msg;
      msg.type = LEDSynthMessages::CONTROL_BUTTON_RELEASE_MSG;
      msg.channel = channel;
      msg.id = midi1.getData1();

      delegate->midiControlReceiveMsg((ControlMsg *)&msg);
    }
    else if (type == MIDIDeviceBase::MidiType::ControlChange)
    {
      ControlValue msg;
      msg.type = LEDSynthMessages::CONTROL_VALUE_MSG;
      msg.channel = channel;
      msg.id = midi1.getData1();
      msg.value = midi1.getData2() / 127.0f;

      delegate->midiControlReceiveMsg((ControlMsg *)&msg);
    }
  }
}
