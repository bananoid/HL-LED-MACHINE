#include <Arduino.h>
#define ARDUINO_ARCH_ESP32
#include "MainController.h"

MainController *mainController;
void setup()
{
  Serial.begin(115200);

  mainController = new MainController();
  mainController->begin();
}

void loop()
{
  mainController->update();
}
