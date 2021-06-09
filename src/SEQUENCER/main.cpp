#include "config.h"
#include "MainController.h"
#include <TaskScheduler.h>
#include "SerialMIDI.h"
#include "Clock.h"

Scheduler runner;
MainController *mainController;
using namespace HLMusicMachine;

void externalClock()
{
    // Serial.println("Clock in");
    mainController->tracker->clock->tick();
}

void externalStart()
{
    // Serial.println("External Start");
    mainController->tracker->clock->play();
}

void externalStop()
{
    // Serial.println("External Stop");
    mainController->tracker->clock->stop();
}

void setup()
{
    Serial.begin(31250);
    mainController = new MainController(&runner);
    // serialMIDI.ports[2]->setHandleClock(externalClock);
    // serialMIDI.ports[2]->setHandleStart(externalStart);
    // serialMIDI.ports[2]->setHandleStop(externalStop);
}

void loop()
{
    mainController->update();
    runner.execute();
    // serialMIDI.update();
}
