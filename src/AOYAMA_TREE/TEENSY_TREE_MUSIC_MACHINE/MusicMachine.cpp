#include "MusicMachine.h"

#include <MIDIInstrument.h>
#include <PinInstrument.h>
#include <Sequencer.h>
#include <Track.h>

#include "AOYAMA_TREE/COMMON/Messages.h"

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

  //Test Message
  testTask.set(16 * TASK_MILLISECOND, TASK_FOREVER, [this]() {
    // Serial.printf("size of TreeStateMessage %i \n", sizeof(TreeStateMessage));
    TreeStateMessage msg;
    msg.parameters.velocityLFO = micros();
    msg.parameters.retrigLFO = cos(millis() / 10233.1234);

    Serial.printf("s %f %f\n", msg.parameters.velocityLFO, msg.parameters.retrigLFO);
    SerialMessengerSingleton->sendMessage(&msg, sizeof(TreeStateMessage));
    // testTask.disable();
  });
  runner->addTask(testTask);
  testTask.enable();

  // tracker->clock->play();
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

void MusicMachine::serialMessengerReceiveData(const uint8_t *incomingData, int len)
{
  uint8_t messageType = SerialMessengerSingleton->getMessageTypeFromData(incomingData);

  switch (messageType)
  {

  case PING:
  {
    BaseMessage pingMessage;
    memcpy(&pingMessage, incomingData, sizeof(pingMessage));
    break;
  }
  case TREE_STATE:
  {
    TreeStateMessage msg;
    memcpy(&msg, incomingData, sizeof(TreeStateMessage));
    unsigned long deltaTime = micros() - msg.parameters.velocityLFO;
    maxPingTime = max(maxPingTime, deltaTime);
    Serial.printf("r %f %f %i %i\n", msg.parameters.velocityLFO, msg.parameters.retrigLFO, deltaTime, maxPingTime);

    // testTask.restart();
    break;
  }
  default:
    break;
  }
}
