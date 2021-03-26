#pragma once //to prevent reimport (singleton)

#include <Arduino.h>

#include "config.h"
#define ARDUINO_ARCH_ESP32
#define _TASK_STD_FUNCTION
#include <TaskSchedulerDeclarations.h>

#include <Bounce2.h>

#include <SerialMessenger.h>
#include <AudioAnalyzer.h>
#include <OledScreen.h>

using namespace HLSerialMessanger;

class LedSynth : SerialMessengerDelegate, AudioAnalyzerDelegate
{
private:
  /* data */
public:
  void begin(Scheduler *runner);
  void update();

  OledScreen *screen;
  Task displayScreen;

  void serialMessengerReceiveMsg(BaseMessage *message) override;
  void serialMessengerReceiveData(const uint8_t *incomingData, int len);

  Bounce2::Button startStopButton = Bounce2::Button();

  void audioAnalyzerOnBandsUpdate(float bandLowVal, float bandMidVal, float bandHighVal) override;

  Task ping;
};