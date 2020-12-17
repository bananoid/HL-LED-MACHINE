#pragma once

#include "MIDIControl/MIDIControl.h"
#include <AudioControl.h>

class MainController : MIDIControlDelegate, HLAudioControl::AudioControlDelegate
{
private:
public:
  MIDIControl *midiControl;
  HLAudioControl::AudioControl *audioControl;
  MainController();
  void begin();
  void update();
  void midiControlReceiveMsg(ControlMsg *message) override;
  void audioControlReceiveMsg(AudioSignalsMsg *message) override;
};
