#include "MainController.h"

#include <MIDIInstrument.h>
#include <PinInstrument.h>
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
  track->retrigLFO = 64;
  track->octave = 3;
  track->noteCount = 4;
  track->noteSpread = 2;
  track->generator->steps = 16;
  track->generator->events = 12;
  track->generator->offset = 0;
  track->chord = 2;
  track->velocity = -1;
  track->velocityLFO = 2;

  //////////////////////////
  track = new Track(sequencer, new MIDIInstrument(1, runner));
  sequencer->appendTrack(track);
  track->stepLenght = 12;
  track->retrig = -1;
  track->retrigLFO = 23;
  track->octave = 4;
  track->noteCount = 6;
  track->noteSpread = 2;
  track->generator->steps = 16;
  track->generator->events = 7;
  track->generator->offset = 0;
  track->chord = 0;
  track->velocity = -1;
  track->velocityLFO = 4.2;

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
  track->velocity = -1;
  track->velocityLFO = 23.24;

  ////////////////////////
  track = new Track(sequencer, new MIDIInstrument(3, runner));
  sequencer->appendTrack(track);
  track->stepLenght = 6;
  track->retrig = 0;
  track->octave = 3;
  track->noteCount = 4;
  track->noteSpread = 2;
  track->generator->steps = 16;
  track->generator->events = 13;
  track->generator->offset = 0;
  track->chord = 0;
  track->velocity = -1;
  track->velocityLFO = 26.24;

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
  track->velocity = -1;
  track->velocityLFO = 29.24;

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
  track->velocity = -1;
  track->velocityLFO = 34.24;

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
  track->velocity = -1;
  track->velocityLFO = 37.24;

  //Percussions
  //// Kick
  track = new Track(sequencer, new MIDIInstrument(6, runner));
  sequencer->appendTrack(track);
  track->type = PERCUSSION;
  track->percussionNote = Note(36); // Kick
  track->stepLenght = 6;
  track->generator->steps = 16;
  track->generator->events = 4;
  track->generator->offset = 0;
  // //// Kick
  // track = new Track(sequencer, new MIDIInstrument(6, runner));
  // sequencer->appendTrack(track);
  // track->type = PERCUSSION;
  // track->percussionNote = Note(36); // Kick
  // track->stepLenght = 6;
  // track->generator->steps = 40;
  // track->generator->events = 3;
  // track->generator->offset = 4;

  //// Rim
  track = new Track(sequencer, new MIDIInstrument(6, runner));
  sequencer->appendTrack(track);
  track->type = PERCUSSION;
  track->percussionNote = Note(37); // Rim
  track->stepLenght = 6;
  track->retrig = 0;
  track->generator->steps = 16;
  track->generator->events = 1;
  track->generator->offset = 0;

  // //// Snare
  // track = new Track(sequencer, new MIDIInstrument(6, runner));
  // sequencer->appendTrack(track);
  // track->type = PERCUSSION;
  // track->percussionNote = Note(38); // Snare
  // track->stepLenght = 6;
  // track->generator->steps = 16;
  // track->generator->events = 2;
  // track->generator->offset = 4;
  // //// Snare
  // track = new Track(sequencer, new MIDIInstrument(6, runner));
  // sequencer->appendTrack(track);
  // track->type = PERCUSSION;
  // track->percussionNote = Note(38); // Snare
  // track->stepLenght = 6;
  // track->generator->steps = 37;
  // track->generator->events = 3;
  // track->generator->offset = 6;

  //// Hihat
  track = new Track(sequencer, new MIDIInstrument(6, runner));
  sequencer->appendTrack(track);
  track->type = PERCUSSION;
  track->percussionNote = Note(42); // Hihat
  track->stepLenght = 6;
  track->retrig = 0;
  track->generator->steps = 16;
  track->generator->events = 6;
  track->generator->offset = 0;

  // Solenoid
  //////////////////////////
  track = new Track(sequencer, new PinIntrument(2, runner)); //ok
  sequencer->appendTrack(track);
  track->stepLenght = 6 * 32;
  // track->retrig = -1;
  track->retrigLFO = 13;
  track->generator->steps = 16;
  track->generator->events = 8;
  track->generator->offset = 0;
  track->velocity = 127;
  // track->velocityLFO = 2;

  // Solenoid
  //////////////////////////
  track = new Track(sequencer, new PinIntrument(2, runner)); //ok
  sequencer->appendTrack(track);
  track->stepLenght = 6;
  // track->retrig = -1;
  track->retrigLFO = 13;
  track->generator->steps = 32;
  track->generator->events = 8;
  track->generator->offset = 0;
  track->velocity = 127;
  // track->velocityLFO = 2;

  //////////////////////////
  track = new Track(sequencer, new PinIntrument(2, runner)); //ok
  sequencer->appendTrack(track);
  track->stepLenght = 6 * 32;
  track->retrig = -1;
  track->retrigLFO = 95;
  track->generator->steps = 32;
  track->generator->events = 7;
  track->generator->offset = 0;
  track->velocity = 127;
  // track->velocityLFO = 2;

  //////////////////////////
  track = new Track(sequencer, new PinIntrument(3, runner)); //ok
  sequencer->appendTrack(track);
  track->stepLenght = 6 * 32;
  track->retrig = -1;
  track->retrigLFO = 13;
  track->generator->steps = 16;
  track->generator->events = 5;
  track->generator->offset = 0;
  track->velocity = 127;
  // track->velocityLFO = 2;

  //////////////////////////
  track = new Track(sequencer, new PinIntrument(3, runner)); //ok
  sequencer->appendTrack(track);
  track->stepLenght = 6;
  // track->retrig = -1;
  track->retrigLFO = 13;
  track->generator->steps = 16;
  track->generator->events = 5;
  track->generator->offset = 0;
  track->velocity = 127;
  // track->velocityLFO = 2;

  //Start Stop button
  startStopButton.attach(9, INPUT_PULLUP); // USE EXTERNAL PULL-UP
  startStopButton.interval(5);
  startStopButton.setPressedState(LOW);
}

void MainController::update()
{

  startStopButton.update();
  if (startStopButton.pressed())
  {
    sequencer->clock->playStop();
    Serial.println("button press");
  }
};
