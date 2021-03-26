#include <Arduino.h>
#include "MIDIUSBHost.h"

#include <USBHost_t36.h> // access to USB MIDI devices (plugged into 2nd USB port)

// USB Host MIDI
USBHost myusb;
USBHub hub1(myusb);
USBHub hub2(myusb);
MIDIDevice midi1(myusb);

namespace HLMIDI
{

  void MIDIUSBHost::begin(MIDIUSBHostDelegate *delegate)
  {
    this->delegate = delegate;
    myusb.begin();
  }

  void MIDIUSBHost::update()
  {
    if (!delegate)
    {
      return;
    }

    while (midi1.read())
    {
      uint8_t channel = midi1.getChannel();
      uint8_t type = midi1.getType();
      uint8_t data1 = midi1.getData1();
      uint8_t data2 = midi1.getData2();

      delegate->MIDIUSBHostOnReceiveData(channel, type, data1, data2);
    }
  };

  MIDIUSBHost *MIDIUSBHostSingleton = new MIDIUSBHost();
}