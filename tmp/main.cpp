#include <Arduino.h>

#if defined(TARGET_ESP32_LED_SERVER)

#define _TASK_STD_FUNCTION
#include <TaskScheduler.h>

Scheduler runner;

#include "ServerMainController.h"
// #include <Server.h>
ServerMainController *mainController;

void setup()
{
  Serial.begin(115200);

  ESPSortedBroadcast::ServerSingleton->begin();

  mainController = new ServerMainController(&runner);

  runner.startNow();
}
void loop()
{
  runner.execute();
}

#elif defined(TARGET_ESP32_LED_CLIENT)

#define _TASK_STD_FUNCTION
#include <TaskScheduler.h>

Scheduler runner;

#include "ClientMainController.h"
ClientMainController *mainController;

void setup()
{
  Serial.begin(115200);

  ESPSortedBroadcast::ClientSingleton->begin();

  mainController = new ClientMainController(&runner);

  runner.startNow();
}
// ----------------------------------

void loop()
{
  runner.execute();
}

#elif defined(TARGET_TEENSY_AUDIO_IN_FFT)

void setup()
{
}

void loop()
{
}

#endif
