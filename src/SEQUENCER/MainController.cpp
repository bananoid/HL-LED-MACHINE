#include "MainController.h"

#include <MIDIInstrument.h>
#include <PinInstrument.h>
#include <Sequencer.h>
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
  sequencer->parameters.stepLenght = 24;
  sequencer->parameters.retrig = 0;
  sequencer->parameters.retrigLFO = 64;
  sequencer->parameters.octave = 3;
  sequencer->parameters.noteCount = 4;
  sequencer->parameters.noteSpread = 2;
  sequencer->parameters.steps = 16;
  sequencer->parameters.events = 12;
  sequencer->parameters.offset = 0;
  sequencer->parameters.chord = 2;
  sequencer->parameters.velocity = -1;
  sequencer->parameters.velocityLFO = 2;

  //////////////////////////
  sequencer = track->addSequencer();
  sequencer->parameters.stepLenght = 12;
  sequencer->parameters.retrig = 0;
  sequencer->parameters.retrigLFO = 23;
  sequencer->parameters.octave = 4;
  sequencer->parameters.noteCount = 6;
  sequencer->parameters.noteSpread = 2;
  sequencer->parameters.steps = 16;
  sequencer->parameters.events = 7;
  sequencer->parameters.offset = 0;
  sequencer->parameters.chord = 0;
  sequencer->parameters.velocity = -1;
  sequencer->parameters.velocityLFO = 4.2;

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
