#include "MainController.h"
#include <Arduino.h>

void MainController::begin()
{
  MIDIUSBHostSingleton->begin(this);
}
void MainController::update()
{
  MIDIUSBHostSingleton->update();
}

void MainController::MIDIUSBHostOnReceiveData(uint8_t channel, uint8_t type, uint8_t data1, uint8_t data2)
{
  Serial.printf("Receive Message");
}
