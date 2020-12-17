#include <Arduino.h>

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
