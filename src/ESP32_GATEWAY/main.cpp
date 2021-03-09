#include <Arduino.h>

#include "MainController.h"

MainController *mainController;
void setup()
{
  mainController = new MainController();
  mainController->begin();
}

void loop()
{
  mainController->update();
}
