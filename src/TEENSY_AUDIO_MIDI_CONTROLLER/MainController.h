#pragma once

#include "MIDIControl/MIDIControl.h"

class MainController : MIDIControlDelegate
{
private:
public:
  MIDIControl *midiControl;
  MainController();
  void begin();
  void update();
  void midiControlReceiveMsg(ControlMsg *message) override;
};
