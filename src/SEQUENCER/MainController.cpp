#include "MainController.h"

#include <MIDIInstrument.h>
#include <Track.h>
#include <EuclideanSequence.h>

using namespace HLSequencer;

MainController::MainController(Scheduler *runner)
{
    sequencer = new Sequencer(runner);

    Track *track;

    //////////////////////////
    track = new Track(sequencer, new MIDIInstrument(1, runner));
    track->gridSize = 6;
    track->generator->steps = 32;
    track->generator->events = 19;
    track->generator->offset = 0;
    sequencer->appendTrack(track);

    //////////////////////////
    track = new Track(sequencer, new MIDIInstrument(2, runner));
    track->gridSize = 6;
    track->retrig = 6;
    track->generator->steps = 16;
    track->generator->events = 2;
    track->generator->offset = 4;
    sequencer->appendTrack(track);

    //////////////////////////
    track = new Track(sequencer, new MIDIInstrument(3, runner));
    track->generator->steps = 16;
    track->generator->events = 7;
    track->generator->offset = 1;
    sequencer->appendTrack(track);

    //////////////////////////
    track = new Track(sequencer, new MIDIInstrument(4, runner));
    track->generator->steps = 12;
    track->generator->events = 6;
    track->generator->offset = 2;
    sequencer->appendTrack(track);
}

void MainController::update(){};
