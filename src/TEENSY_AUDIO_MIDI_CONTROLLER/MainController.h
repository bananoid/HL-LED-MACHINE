#pragma once

#include "MIDIControl/MIDIControl.h"
#include <AudioControl.h>

#include <SerialMessenger.h>

using namespace HLSerialMessanger;

class MainController : MIDIControlDelegate, HLAudioControl::AudioControlDelegate
{
private:
public:
  MIDIControl *midiControl;
  HLAudioControl::AudioControl *audioControl;
  SerialMessenger *serialMessangerTx;
  MainController();
  void begin();
  void update();
  void midiControlReceiveMsg(ControlMsg *message) override;
  void audioControlReceiveMsg(AudioSignalsMsg *message) override;
};
