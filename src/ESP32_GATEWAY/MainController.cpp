#include "MainController.h"
#include <Arduino.h>

#define BOUD_RATE 1000000

MainController::MainController()
{
  pinMode(13, OUTPUT);

  Serial.begin(BOUD_RATE);
  Serial2.begin(BOUD_RATE);

  SerialMessengerSingleton->delegate = this;
}

void MainController::begin()
{
  SerialMessengerSingleton->begin(&Serial2, BOUD_RATE);
}
void MainController::update()
{

  unsigned long curTime = millis();
  if (lastTime != curTime)
  {
    lastTime = curTime;

    if ((curTime) % 100 == 0)
    {

      Message m;
      m.type = (curTime / 100) % 256;
      Serial.println(m.type);
      SerialMessengerSingleton->sendMessage(&m);
    }
  }
  SerialMessengerSingleton->update();
}

void MainController::serialMessengerReceiveMsg(Message *message)
{
}