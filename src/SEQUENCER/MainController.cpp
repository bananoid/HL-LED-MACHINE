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
    track->stepLenght = 32;
    track->retrig = -1;
    track->octave = 2;
    track->noteCount = 4;
    track->noteSpread = 2;
    track->generator->steps = 16;
    track->generator->events = 16;
    track->generator->offset = 0;
    sequencer->appendTrack(track);

    //////////////////////////
    track = new Track(sequencer, new MIDIInstrument(2, runner));
    track->stepLenght = 24;
    track->retrig = 12; //retrig lfo
    track->octave = 2;
    track->noteCount = 4;
    track->noteSpread = 2;
    track->generator->steps = 16;
    track->generator->events = 2;
    track->generator->offset = 4;
    sequencer->appendTrack(track);

    //////////////////////////
    track = new Track(sequencer, new MIDIInstrument(3, runner));
    track->stepLenght = 12;
    track->retrig = 2;
    track->octave = 4;
    track->noteCount = 4;
    track->noteSpread = 2;
    track->generator->steps = 16;
    track->generator->events = 5;
    track->generator->offset = 0;
    sequencer->appendTrack(track);

    //////////////////////////
    track = new Track(sequencer, new MIDIInstrument(4, runner));
    track->stepLenght = 48;
    track->retrig = 0;
    track->octave = 2;
    track->noteCount = 4;
    track->noteSpread = 2;
    track->generator->steps = 16;
    track->generator->events = 7;
    track->generator->offset = 0;
    sequencer->appendTrack(track);

    //////////////////////////
    track = new Track(sequencer, new MIDIInstrument(5, runner));
    track->stepLenght = 24;
    track->retrig = 0;
    track->octave = 2;
    track->noteCount = 4;
    track->noteSpread = 2;
    track->generator->steps = 16;
    track->generator->events = 6;
    track->generator->offset = 0;
    sequencer->appendTrack(track);
}

void MainController::update(){};
