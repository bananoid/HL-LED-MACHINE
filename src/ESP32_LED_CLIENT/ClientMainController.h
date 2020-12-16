#ifndef HL_SRC_CLIENTMAINCONTROLLER
#define HL_SRC_CLIENTMAINCONTROLLER

#include <Arduino.h>
#include <FastLEDRenderer.h>
#include <GFXUtils.h>
#include <Client.h>

// #define LS_NUM_LEDS_PER_STRIP 300
// #define LS_NUM_STRIPS 1
// #define LS_DATA_PIN 2

#include <LEDSynth.h>

#define _TASK_STD_FUNCTION
// #define _TASK_MICRO_RES
#include <TaskSchedulerDeclarations.h>

#define RENDER_FRAME_TIME TASK_MILLISECOND * 16 // ms

class ClientMainController : ESPSortedBroadcast::ClientDelegate
{
private:
public:
  LEDStrips::FastLEDRenderer ledRenderer;
  LEDSynth::LEDSynth *ledSynth;

  long frameTime;

  ClientMainController(Scheduler *runner);

  Scheduler *runner;

  Task frameRenderTask;
  void frameRender();

  Task requestClientIndexTask;

  // void benckMarkFPS();

  void renderCurrentIndex();

  void clientReceveSyncAction(ESPSortedBroadcast::SyncAction data) override;
  void clientReceveClientIndex(ESPSortedBroadcast::SendIdAction data) override;
};

#endif /* HL_SRC_CLIENTMAINCONTROLLER */
