#pragma once

#include <MIDIUSBHost.h>

using namespace HLMIDI;

class MainController : MIDIUSBHostDelegate
{
private:
public:
  void begin();
  void update();
  void MIDIUSBHostOnReceiveData(uint8_t channel, uint8_t type, uint8_t data1, uint8_t data2) override;
};
