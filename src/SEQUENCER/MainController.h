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

#define NUM_OF_SCALES 0
#define NUM_OF_CV_TRAKS 8
#define NUM_OF_MIDI_TRAKS 0

#include "UI.h"

struct GlobalSettings
{
    Sequencer::Parameters trackParams[NUM_OF_CV_TRAKS];
    bool tracksEnabled[NUM_OF_CV_TRAKS];
};

class MainController : UIDelegate
{
private:
    /* data */
public:
    MainController(Scheduler *runner);
    void update();

    HLMusicMachine::Tracker *tracker;
    void updateMIDI();

    Sequencer *cvSequencers[NUM_OF_CV_TRAKS];
    Track *cvTracks[NUM_OF_CV_TRAKS];

    Sequencer *midiSequencers[NUM_OF_MIDI_TRAKS];
    Track *midiTracks[NUM_OF_MIDI_TRAKS];

    bool midiUIInvalid = true;
    void drawMidiInterface();
    Task midiUIDrawTask;

    Task uiTask;

    GlobalSettings globalSettings;
    bool globalSettingsUnsaved = false;
    void saveGlobalSettings();
    void loadGlobalSettings();
};
