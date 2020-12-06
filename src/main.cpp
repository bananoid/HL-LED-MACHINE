#include <Arduino.h>

// #define IS_SERVER // Comment for client mode

#include <ESPSortedBroadcast.h>
// #include <Server.h>

#ifdef IS_SERVER

void setup()
{
  Serial.begin(115200);

  ESPSortedBroadcast::ServerSingleton->begin();
}

void loop()
{
  ESPSortedBroadcast::ServerSingleton->update();
}

#else

// #include <FastLED.h>

#include <FastLEDRenderer.h>
#include <GFXUtils.h>
#include <Client.h>

LEDStrips::FastLEDRenderer ledRenderer;

#define LS_NUM_LEDS_PER_STRIP 300
#define LS_NUM_STRIPS 1
#define LS_DATA_PIN 2

#include <LEDSynth.h>

LEDSynth::LEDSynth *ledSynth;

#define _TASK_SLEEP_ON_IDLE_RUN
#include <TaskScheduler.h>
Scheduler runner;
// Callback methods prototypes
void frameRender();
void benckMarkFPS();

// Tasks
Task t1(16, TASK_FOREVER, &frameRender, &runner, true);    //adding task to the chain on creation
Task t2(1000, TASK_FOREVER, &benckMarkFPS, &runner, true); //adding task to the chain on creation

long frameTime;

void frameRender()
{
  // Serial.print("t2: ");
  // Serial.println(millis());
  unsigned long curTime = micros();
  ledSynth->update();
  frameTime = micros() - curTime;
}

void benckMarkFPS()
{
  Serial.print("Frame time :: ");
  Serial.println(frameTime);
}

void setup()
{
  Serial.begin(115200);

  ESPSortedBroadcast::ClientSingleton->begin();

  ledRenderer.begin();
  ledSynth = new LEDSynth::LEDSynth(&ledRenderer);

  runner.startNow();
}

void loop()
{
  // ESPSortedBroadcast::ClientSingleton->update();

  // int clientInx = ESPSortedBroadcast::ClientSingleton->clientId;

  // for (size_t i = 0; i < LS_NUM_LEDS_PER_STRIP; i++)
  // {
  //   GFXUtils::fRGB color;
  //   if (i + 1 <= clientInx)
  //   {
  //     color = GFXUtils::fRGB(0, 0, 1);
  //   }
  //   else
  //   {
  //     color = GFXUtils::fRGB(1, 0, 0);
  //   }
  //   ledRenderer.setPixel(i, color);
  // }
  // ledRenderer.show();

  runner.execute();
}
#endif