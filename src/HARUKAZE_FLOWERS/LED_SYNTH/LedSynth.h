#pragma once //to prevent reimport (singleton)

#include <Arduino.h>

#include "config.h"
#include "HARUKAZE_FLOWERS/COMMON/Messages.h"
#define ARDUINO_ARCH_ESP32
#define _TASK_STD_FUNCTION
#include <TaskSchedulerDeclarations.h>

#include <Bounce2.h>

#include <SerialMessenger.h>
#include <AudioAnalyzer.h>

#define OLEDSCREEN_DISABLED
#ifndef OLEDSCREEN_DISABLED
#include <OledScreen.h>
#endif

#include <MIDIUSBHost.h>

using namespace HLSerialMessanger;
using namespace HLMIDI;

class LedSynth : SerialMessengerDelegate, AudioAnalyzerDelegate, MIDIUSBHostDelegate
{
private:
  /* data */
public:
  void begin(Scheduler *runner);
  void update();
#ifndef OLEDSCREEN_DISABLED
  OledScreen *screen;
  Task displayScreen;
#endif

  void serialMessengerReceiveMsg(BaseMessage *message) override;
  void serialMessengerReceiveData(const uint8_t *incomingData, int len);

  Bounce2::Button startStopButton = Bounce2::Button();

  void audioAnalyzerOnBandsUpdate(float bandLowVal, float bandMidVal, float bandHighVal) override;

  void MIDIUSBHostOnReceiveData(uint8_t channel, uint8_t type, uint8_t data1, uint8_t data2) override;

  Task ping;

  Task broadcastAudioBandsTask;
  Task broadcastMIDITask;

  LedSynthLayerColorMessage *ledSynthLayerColorMessages[N_LAYERS];
  LedSynthLayerShapeMessage *ledSynthLayerShapeMessages[N_LAYERS];
  LedSynthLayerAudioMessage *ledSynthLayerAudioMessages[N_LAYERS];
  LedSynthGlobalMessage *ledSynthGlobalMessage;

  // messages
  bool globalChanged = false;
  bool layer1ColorChanged = false;
  bool layer1ShapeChanged = false;
  bool layer1AudioChanged = false;
  bool layer2ColorChanged = false;
  bool layer2ShapeChanged = false;
  bool layer2AudioChanged = false;
};