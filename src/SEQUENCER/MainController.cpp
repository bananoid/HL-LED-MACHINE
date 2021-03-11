#include "MainController.h"

#include <MIDIInstrument.h>
#include <Track.h>
#include <EuclideanSequence.h>

using namespace HLSequencer;

MainController::MainController(Scheduler *runner)
{
    sequencer = new Sequencer(runner);

    MIDIInstrument *instrument;
    Track *track;
    EuclideanSequence *sequence;

    //////////////////////////
    instrument = new MIDIInstrument(1, runner);
    instrument->delegate = sequencer;
    instrument->defaultNote = 36; // Kick

    sequence = new EuclideanSequence();
    sequence->steps = 18;
    sequence->events = 7;

    track = new Track(instrument);
    track->appendSequence(sequence);

    sequencer->appendTrack(track);

    // /////////////////////////
    // instrument = new MIDIInstrument(1, runner);
    // instrument->delegate = sequencer;
    // instrument->defaultNote = 38; // Snare

    // sequence = new EuclideanSequence();
    // sequence->steps = 16;
    // sequence->events = 2;
    // sequence->offset = 4;

    // track = new Track(instrument);
    // track->appendSequence(sequence);

    // sequencer->appendTrack(track);

    // /////////////////////////
    // instrument = new MIDIInstrument(1, runner);
    // instrument->delegate = sequencer;
    // instrument->defaultNote = 42; // Hihat

    // sequence = new EuclideanSequence();
    // sequence->steps = 16;
    // sequence->events = 13;
    // sequence->offset = 0;

    // track = new Track(instrument);
    // track->appendSequence(sequence);

    // sequencer->appendTrack(track);

    // /////////////////////////
    // instrument = new MIDIInstrument(1, runner);
    // instrument->delegate = sequencer;
    // instrument->defaultNote = 37; // Rim

    // sequence = new EuclideanSequence();
    // sequence->steps = 12;
    // sequence->events = 5;
    // sequence->offset = 2;

    // track = new Track(instrument);
    // track->appendSequence(sequence);

    // sequencer->appendTrack(track);
}

void MainController::update(){};
