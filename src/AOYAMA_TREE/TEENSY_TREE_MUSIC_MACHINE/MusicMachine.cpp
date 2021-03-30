#include "MusicMachine.h"

#include <MIDIInstrument.h>
#include <PinInstrument.h>
#include <Sequencer.h>
#include <Track.h>

using namespace HLMusicMachine;

MusicMachine::MusicMachine(Scheduler *runner)
{
  tracker = new Tracker(runner);

  Track *track;
  Sequencer *sequencer;

  track = new Track(tracker, new MIDIInstrument(1, runner));
  Sequencer::Parameters params;
  //////////////////////////
  params.stepLenght = 3;
  params.retrig = -1;
  params.retrigLFO = 64;
  params.octave = 3;
  params.noteCount = 4;
  params.noteSpread = 2;
  params.steps = 32;
  params.events = 12;
  params.offset = 0;
  params.chord = 2;
  params.velocity = -1;
  params.velocityLFO = 2;

  sequencer = track->addSequencer();
  sequencer->parameters = params;
  params.events = 1;
  params.stepLenght = 1;
  params.noteCount = 1;
  sequencer->minParameters = params;
  params.events = 16;
  params.stepLenght = 8;
  params.noteCount = 7;
  sequencer->maxParameters = params;
  sequencer->randomize();

  //////////////////////////
  sequencer = track->addSequencer();
  params.stepLenght = 3;
  params.retrig = -1;
  params.retrigLFO = 23;
  params.octave = 4;
  params.noteCount = 6;
  params.noteSpread = 2;
  params.steps = 32;
  params.events = 7;
  params.offset = 0;
  params.chord = 0;
  params.velocity = -1;
  params.velocityLFO = 4.2;

  sequencer = track->addSequencer();
  sequencer->parameters = params;
  params.events = 1;
  params.stepLenght = 3;
  params.noteCount = 1;
  sequencer->minParameters = params;
  params.events = 16;
  params.stepLenght = 6;
  params.noteCount = 8;
  sequencer->maxParameters = params;
  sequencer->randomize();

  tracker->appendTrack(track);

  //Start Stop button
  startStopButton.attach(9, INPUT_PULLUP); // USE EXTERNAL PULL-UP
  startStopButton.interval(5);
  startStopButton.setPressedState(LOW);

  // Serial Messenger
  Serial.begin(BAUD_RATE);
  Serial6.begin(BAUD_RATE);
  SerialMessengerSingleton->delegate = this;
  SerialMessengerSingleton->begin(&Serial6, BAUD_RATE);
}

void MusicMachine::update()
{
  // button
  startStopButton.update();
  if (startStopButton.pressed())
  {
    tracker->clock->playStop();
    Serial.println("button press");
  }

  // serial messenger
  SerialMessengerSingleton->update();
}

void MusicMachine::serialMessengerReceiveMsg(BaseMessage *message)
{
  Serial.println("Receive Serial message!");
};

void MusicMachine::serialMessengerReceiveData(const uint8_t *incomingData, int len)
{
  Serial.println("Receive Serial data");
}
