#pragma once

#include "MIDIControl.h"
#include <AudioControl.h>

#include <SerialMessenger.h>

using namespace HLSerialMessanger;

class MainController : MIDIControlDelegate, HLAudioControl::AudioControlDelegate, SerialMessengerDelegate
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
  void serialMessengerReceiveMsg(Message *message) override;

  unsigned long lastTime;
};
