#include "MainController.h"

#include <MIDIInstrument.h>
#include <PinInstrument.h>
#include <Sequencer.h>
#include <EuclideanSequence.h>

using namespace HLMusicMachine;

MainController::MainController(Scheduler *runner)
{
  tracker = new Tracker(runner);

  Sequencer *sequencer;

  //////////////////////////
  sequencer = new Sequencer(tracker, new MIDIInstrument(1, runner));
  tracker->appendTrack(sequencer);
  sequencer->stepLenght = 24;
  sequencer->retrig = -1;
  sequencer->retrigLFO = 64;
  sequencer->octave = 3;
  sequencer->noteCount = 4;
  sequencer->noteSpread = 2;
  sequencer->generator->steps = 16;
  sequencer->generator->events = 12;
  sequencer->generator->offset = 0;
  sequencer->chord = 2;
  sequencer->velocity = -1;
  sequencer->velocityLFO = 2;

  //////////////////////////
  sequencer = new Sequencer(tracker, new MIDIInstrument(1, runner));
  tracker->appendTrack(sequencer);
  sequencer->stepLenght = 12;
  sequencer->retrig = -1;
  sequencer->retrigLFO = 23;
  sequencer->octave = 4;
  sequencer->noteCount = 6;
  sequencer->noteSpread = 2;
  sequencer->generator->steps = 16;
  sequencer->generator->events = 7;
  sequencer->generator->offset = 0;
  sequencer->chord = 0;
  sequencer->velocity = -1;
  sequencer->velocityLFO = 4.2;

  ////////////////////////
  sequencer = new Sequencer(tracker, new MIDIInstrument(2, runner));
  tracker->appendTrack(sequencer);
  sequencer->stepLenght = 24;
  sequencer->retrig = 12;
  sequencer->octave = 3;
  sequencer->noteCount = 4;
  sequencer->noteSpread = 2;
  sequencer->generator->steps = 16;
  sequencer->generator->events = 2;
  sequencer->generator->offset = 4;
  sequencer->chord = 0;
  sequencer->velocity = -1;
  sequencer->velocityLFO = 23.24;

  ////////////////////////
  sequencer = new Sequencer(tracker, new MIDIInstrument(3, runner));
  tracker->appendTrack(sequencer);
  sequencer->stepLenght = 6;
  sequencer->retrig = 0;
  sequencer->octave = 3;
  sequencer->noteCount = 4;
  sequencer->noteSpread = 2;
  sequencer->generator->steps = 16;
  sequencer->generator->events = 13;
  sequencer->generator->offset = 0;
  sequencer->chord = 0;
  sequencer->velocity = -1;
  sequencer->velocityLFO = 26.24;

  ////////////////////////
  sequencer = new Sequencer(tracker, new MIDIInstrument(4, runner));
  tracker->appendTrack(sequencer);
  sequencer->stepLenght = 48;
  sequencer->retrig = 0;
  sequencer->octave = 3;
  sequencer->noteCount = 4;
  sequencer->noteSpread = 2;
  sequencer->generator->steps = 16;
  sequencer->generator->events = 7;
  sequencer->generator->offset = 0;
  sequencer->chord = 0;
  sequencer->velocity = -1;
  sequencer->velocityLFO = 29.24;

  //////////////////////////
  sequencer = new Sequencer(tracker, new MIDIInstrument(5, runner));
  tracker->appendTrack(sequencer);
  sequencer->stepLenght = 24;
  sequencer->retrig = 12;
  sequencer->octave = 1;
  sequencer->noteCount = 1;
  sequencer->noteSpread = 2;
  sequencer->generator->steps = 16;
  sequencer->generator->events = 11;
  sequencer->generator->offset = 0;
  sequencer->chord = 0;
  sequencer->velocity = -1;
  sequencer->velocityLFO = 34.24;

  //////////////////////////
  sequencer = new Sequencer(tracker, new MIDIInstrument(5, runner));
  tracker->appendTrack(sequencer);
  sequencer->stepLenght = 48;
  sequencer->retrig = 16;
  sequencer->octave = 2;
  sequencer->noteCount = 5;
  sequencer->noteSpread = 7;
  sequencer->generator->steps = 16;
  sequencer->generator->events = 5;
  sequencer->generator->offset = 3;
  sequencer->chord = 0;
  sequencer->velocity = -1;
  sequencer->velocityLFO = 37.24;

  //Percussions
  //// Kick
  sequencer = new Sequencer(tracker, new MIDIInstrument(6, runner));
  tracker->appendTrack(sequencer);
  sequencer->type = PERCUSSION;
  sequencer->percussionNote = Note(36); // Kick
  sequencer->stepLenght = 6;
  sequencer->generator->steps = 16;
  sequencer->generator->events = 4;
  sequencer->generator->offset = 0;
  // //// Kick
  // track = new Track(tracker, new MIDIInstrument(6, runner));
  // tracker->appendTrack(track);
  // track->type = PERCUSSION;
  // track->percussionNote = Note(36); // Kick
  // track->stepLenght = 6;
  // track->generator->steps = 40;
  // track->generator->events = 3;
  // track->generator->offset = 4;

  //// Rim
  sequencer = new Sequencer(tracker, new MIDIInstrument(6, runner));
  tracker->appendTrack(sequencer);
  sequencer->type = PERCUSSION;
  sequencer->percussionNote = Note(37); // Rim
  sequencer->stepLenght = 6;
  sequencer->retrig = 0;
  sequencer->generator->steps = 16;
  sequencer->generator->events = 1;
  sequencer->generator->offset = 0;

  // //// Snare
  // track = new Track(tracker, new MIDIInstrument(6, runner));
  // tracker->appendTrack(track);
  // track->type = PERCUSSION;
  // track->percussionNote = Note(38); // Snare
  // track->stepLenght = 6;
  // track->generator->steps = 16;
  // track->generator->events = 2;
  // track->generator->offset = 4;
  // //// Snare
  // track = new Track(tracker, new MIDIInstrument(6, runner));
  // tracker->appendTrack(track);
  // track->type = PERCUSSION;
  // track->percussionNote = Note(38); // Snare
  // track->stepLenght = 6;
  // track->generator->steps = 37;
  // track->generator->events = 3;
  // track->generator->offset = 6;

  //// Hihat
  sequencer = new Sequencer(tracker, new MIDIInstrument(6, runner));
  tracker->appendTrack(sequencer);
  sequencer->type = PERCUSSION;
  sequencer->percussionNote = Note(42); // Hihat
  sequencer->stepLenght = 6;
  sequencer->retrig = 0;
  sequencer->generator->steps = 16;
  sequencer->generator->events = 6;
  sequencer->generator->offset = 0;

  // Solenoid
  //////////////////////////
  sequencer = new Sequencer(tracker, new PinIntrument(2, runner)); //ok
  tracker->appendTrack(sequencer);
  sequencer->stepLenght = 6 * 32;
  // track->retrig = -1;
  sequencer->retrigLFO = 13;
  sequencer->generator->steps = 16;
  sequencer->generator->events = 8;
  sequencer->generator->offset = 0;
  sequencer->velocity = 127;
  // track->velocityLFO = 2;

  // Solenoid
  //////////////////////////
  sequencer = new Sequencer(tracker, new PinIntrument(2, runner)); //ok
  tracker->appendTrack(sequencer);
  sequencer->stepLenght = 6;
  // track->retrig = -1;
  sequencer->retrigLFO = 13;
  sequencer->generator->steps = 32;
  sequencer->generator->events = 8;
  sequencer->generator->offset = 0;
  sequencer->velocity = 127;
  // track->velocityLFO = 2;

  //////////////////////////
  sequencer = new Sequencer(tracker, new PinIntrument(2, runner)); //ok
  tracker->appendTrack(sequencer);
  sequencer->stepLenght = 6 * 32;
  sequencer->retrig = -1;
  sequencer->retrigLFO = 95;
  sequencer->generator->steps = 32;
  sequencer->generator->events = 7;
  sequencer->generator->offset = 0;
  sequencer->velocity = 127;
  // track->velocityLFO = 2;

  //////////////////////////
  sequencer = new Sequencer(tracker, new PinIntrument(3, runner)); //ok
  tracker->appendTrack(sequencer);
  sequencer->stepLenght = 6 * 32;
  sequencer->retrig = -1;
  sequencer->retrigLFO = 13;
  sequencer->generator->steps = 16;
  sequencer->generator->events = 5;
  sequencer->generator->offset = 0;
  sequencer->velocity = 127;
  // track->velocityLFO = 2;

  //////////////////////////
  sequencer = new Sequencer(tracker, new PinIntrument(3, runner)); //ok
  tracker->appendTrack(sequencer);
  sequencer->stepLenght = 6;
  // track->retrig = -1;
  sequencer->retrigLFO = 13;
  sequencer->generator->steps = 16;
  sequencer->generator->events = 5;
  sequencer->generator->offset = 0;
  sequencer->velocity = 127;
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
    tracker->clock->playStop();
    Serial.println("button press");
  }
};
