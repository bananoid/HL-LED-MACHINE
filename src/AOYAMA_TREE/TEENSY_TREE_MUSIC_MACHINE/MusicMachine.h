#pragma once //to prevent reimport (singleton)

#include <Arduino.h>

#include "config.h"
#include <TaskSchedulerDeclarations.h>

#include <Tracker.h>
#include <Bounce2.h>

#include <SerialMessenger.h>

using namespace HLSerialMessanger;

class MusicMachine : SerialMessengerDelegate
{
private:
  /* data */
public:
  MusicMachine(Scheduler *runner);

  void begin();
  void update();
  void serialMessengerReceiveMsg(BaseMessage *message) override;

  Bounce2::Button startStopButton = Bounce2::Button();

  HLMusicMachine::Tracker *tracker;
};