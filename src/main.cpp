#include <Arduino.h>

// #define IS_SERVER // Comment for client mode

#include <Server.h>

#define _TASK_SLEEP_ON_IDLE_RUN
#include <TaskScheduler.h>
Scheduler runner;

#ifdef IS_SERVER

// Callback methods prototypes
void sendParameters();
void sendSync();

// Tasks
Task t1(16, TASK_FOREVER, &sendParameters, &runner, true);
Task t2(1000, TASK_FOREVER, &sendSync, &runner, true);

void setup()
{
  Serial.begin(115200);

  ESPSortedBroadcast::ServerSingleton->begin();

  runner.startNow();
}

void loop()
{
  runner.execute();
}

void sendParameters()
{
  ESPSortedBroadcast::ServerSingleton->update();
}

void sendSync()
{
  ESPSortedBroadcast::ServerSingleton->broadCastCurrentPosition();
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

// Callback methods prototypes
void frameRender();
void benckMarkFPS();
void clientUpdate();

// Tasks
Task t1(16, TASK_FOREVER, &frameRender, &runner, true);
Task t2(1000, TASK_FOREVER, &benckMarkFPS, &runner, true);
Task t3(200, TASK_FOREVER, &clientUpdate, &runner, true);

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

void clientUpdate()
{
  int clientInx = ESPSortedBroadcast::ClientSingleton->clientId;
  if (clientInx > 0)
  {
    Serial.print("Client index :: ");
    Serial.println(clientInx);
    t3.disable();
    ledSynth->index = clientInx - 1;
    return;
  }
  ESPSortedBroadcast::ClientSingleton->update();
  Serial.println("Request Client Index");
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