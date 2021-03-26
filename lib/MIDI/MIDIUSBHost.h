#pragma once
#include <Arduino.h>
// #include <ControlMessages.h>
// #include <LEDSyntMessages.h>

namespace HLMIDI
{

  class MIDIUSBHostDelegate
  {
  public:
    virtual void MIDIUSBHostOnReceiveData(uint8_t channel, uint8_t type, uint8_t data1, uint8_t data2);
  };

  class MIDIUSBHost
  {
  private:
  public:
    MIDIUSBHostDelegate *delegate;
    void begin(MIDIUSBHostDelegate *delegate);
    void update();
  };

  extern MIDIUSBHost *MIDIUSBHostSingleton;
}