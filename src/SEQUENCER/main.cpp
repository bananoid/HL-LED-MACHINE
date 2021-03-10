#include "config.h"
#include "MainController.h"
#include <TaskScheduler.h>

Scheduler runner;
MainController *mainController;

void setup()
{
    Serial.begin(2000000);
    mainController = new MainController(&runner);
}

void loop()
{
    mainController->update();
    runner.execute();
}
