#include "MainController.h"

#include <MIDIInstrument.h>
#include <PinInstrument.h>
#include <Sequencer.h>
#include <Track.h>
#include "SerialMIDI.h"

using namespace HLMusicMachine;

MainController::MainController(Scheduler *runner)
{
  serialMIDI.begin();

  tracker = new Tracker(runner);

  Track *track;
  Sequencer *sequencer;

  Sequencer::Parameters params;

  //////////////////////////
  track = new Track(tracker, new MIDIInstrument(1, runner));
  sequencer = track->addSequencer();
  sequencer->parameters.stepLenght = 3;
  sequencer->parameters.retrig = 0;
  sequencer->parameters.retrigLFO = 84;
  sequencer->parameters.octave = 0;
  sequencer->parameters.noteCount = 3;
  sequencer->parameters.noteOffset = 2;
  sequencer->parameters.noteSpread = 2;
  sequencer->parameters.steps = 16;
  sequencer->parameters.events = 4;
  sequencer->parameters.offset = 0;
  sequencer->parameters.chord = 0;
  // sequencer->parameters.velocity = 0;
  // sequencer->parameters.velocityLFO = 2;
  sequencer->parameters.arpeggioType = Sequencer::ArpeggioType_Eucledian;
  // sequencer->parameters.arpeggioType = Sequencer::ArpeggioType_LFO;
  sequencer->parameters.arpeggioLFO = 1;
  tracker->appendTrack(track);
  track->play();

  //////////////////////////
  // track = new Track(tracker, new MIDIInstrument(2, runner));
  // params.stepLenght = 5;
  // params.retrig = -1;
  // params.retrigLFO = 58;
  // params.octave = 0;
  // params.noteCount = 7;
  // params.noteSpread = 2;
  // params.steps = 16;
  // params.events = 7;
  // params.offset = 0;
  // params.chord = 0;
  // params.velocity = -1;
  // params.velocityLFO = 2;
  // sequencer = track->addSequencer();
  // sequencer->parameters = params;
  // tracker->appendTrack(track);
  // track->play();

  //////////////////////////
  // track = new Track(tracker, new MIDIInstrument(3, runner));
  // params.stepLenght = 1;
  // params.retrig = 0;
  // params.retrigLFO = 58;
  // params.octave = 0;
  // params.noteCount = 7;
  // params.noteSpread = 2;
  // params.steps = 16;
  // params.events = 5;
  // params.offset = 0;
  // params.chord = 0;
  // params.velocity = -1;
  // params.velocityLFO = 2;
  // params.arpeggioType = Sequencer::ArpeggioType_LFO;
  // sequencer = track->addSequencer();
  // sequencer->parameters = params;
  // tracker->appendTrack(track);
  // track->play();

  tracker->clock->play();

  //Start Stop button
  startStopButton.attach(32, INPUT_PULLUP); // USE EXTERNAL PULL-UP
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
