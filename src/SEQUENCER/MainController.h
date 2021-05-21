#pragma once //to prevent reimport (singleton)

#include <Arduino.h>

#include "config.h"
#include <TaskSchedulerDeclarations.h>

#include <Tracker.h>
#include <Bounce2.h>

#include <MIDIInstrument.h>
#include <PinInstrument.h>
#include <Sequencer.h>
#include <Track.h>

using namespace HLMusicMachine;

class MainController
{
private:
    /* data */
public:
    MainController(Scheduler *runner);
    void update();
    Bounce2::Button startStopButton = Bounce2::Button();

    HLMusicMachine::Tracker *tracker;
    void updateMIDI();

    Sequencer *cvSequencers[4];
};
