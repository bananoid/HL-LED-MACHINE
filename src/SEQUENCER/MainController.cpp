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
    sequencer->appendTrack(track);
    track->stepLenght = 24;
    track->retrig = -1;
    track->octave = 3;
    track->noteCount = 4;
    track->noteSpread = 2;
    track->generator->steps = 16;
    track->generator->events = 12;
    track->generator->offset = 0;
    track->chord = 2;

    //////////////////////////
    track = new Track(sequencer, new MIDIInstrument(1, runner));
    sequencer->appendTrack(track);
    track->stepLenght = 12;
    track->retrig = -1;
    track->octave = 4;
    track->noteCount = 6;
    track->noteSpread = 2;
    track->generator->steps = 16;
    track->generator->events = 7;
    track->generator->offset = 0;
    track->chord = 0;

    ////////////////////////
    track = new Track(sequencer, new MIDIInstrument(2, runner));
    sequencer->appendTrack(track);
    track->stepLenght = 24;
    track->retrig = 12;
    track->octave = 3;
    track->noteCount = 4;
    track->noteSpread = 2;
    track->generator->steps = 16;
    track->generator->events = 2;
    track->generator->offset = 4;
    track->chord = 0;

    ////////////////////////
    track = new Track(sequencer, new MIDIInstrument(3, runner));
    sequencer->appendTrack(track);
    track->stepLenght = 6;
    track->retrig = 0;
    track->octave = 3;
    track->noteCount = 4;
    track->noteSpread = 2;
    track->generator->steps = 12;
    track->generator->events = 10;
    track->generator->offset = 0;
    track->chord = 0;

    ////////////////////////
    track = new Track(sequencer, new MIDIInstrument(4, runner));
    sequencer->appendTrack(track);
    track->stepLenght = 48;
    track->retrig = 0;
    track->octave = 3;
    track->noteCount = 4;
    track->noteSpread = 2;
    track->generator->steps = 16;
    track->generator->events = 7;
    track->generator->offset = 0;
    track->chord = 0;

    //////////////////////////
    track = new Track(sequencer, new MIDIInstrument(5, runner));
    sequencer->appendTrack(track);
    track->stepLenght = 24;
    track->retrig = 12;
    track->octave = 1;
    track->noteCount = 1;
    track->noteSpread = 2;
    track->generator->steps = 16;
    track->generator->events = 11;
    track->generator->offset = 0;
    track->chord = 0;

    //////////////////////////
    track = new Track(sequencer, new MIDIInstrument(5, runner));
    sequencer->appendTrack(track);
    track->stepLenght = 48;
    track->retrig = 16;
    track->octave = 2;
    track->noteCount = 5;
    track->noteSpread = 7;
    track->generator->steps = 16;
    track->generator->events = 5;
    track->generator->offset = 3;
    track->chord = 0;
}

void MainController::update(){};
