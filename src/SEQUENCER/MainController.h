#pragma once //to prevent reimport (singleton)

#include <Arduino.h>

#include "config.h"
#include <TaskSchedulerDeclarations.h>

#include <Sequencer.h>

class MainController
{
private:
    /* data */
public:
    MainController(Scheduler *runner);
    void update();

    HLSequencer::Sequencer *sequencer;
};
