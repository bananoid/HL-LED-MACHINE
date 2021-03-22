#include "MainController.h"

#include <MIDIInstrument.h>
#include <PinInstrument.h>
#include <Sequencer.h>
#include <EuclideanSequence.h>
#include <Track.h>

using namespace HLMusicMachine;

MainController::MainController(Scheduler *runner)
{
  tracker = new Tracker(runner);

  Track *track;
  Sequencer *sequencer;

  track = new Track(tracker, new MIDIInstrument(1, runner));
  //////////////////////////
  sequencer = track->addSequencer();
  sequencer->stepLenght = 24;
  sequencer->retrig = 0;
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
  sequencer = track->addSequencer();
  sequencer->stepLenght = 12;
  sequencer->retrig = 0;
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

  tracker->appendTrack(track);

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
