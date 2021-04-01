#include "MusicMachine.h"

#include "AOYAMA_TREE/COMMON/Messages.h"
#include "AOYAMA_TREE/COMMON/TrackerFactory.h"

using namespace HLMusicMachine;

MusicMachine::MusicMachine(Scheduler *runner)
{
  this->runner = runner;
  tracker = new Tracker(runner);
  tracker->delegate = this;
  TrackerFactory::buildSong(tracker, NUMBER_OF_FLOWERS);
  initFlowerStates();
  tracker->clock->play();

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
  benchmarkTask.set(200 * TASK_MILLISECOND, TASK_FOREVER, [this]() {
    BenchmarkMessage msg;
    msg.time = micros();
    Serial.printf("T Benchmark time %i\n", msg.time);
    SerialMessengerSingleton->sendMessage(&msg, sizeof(BenchmarkMessage));
  });
  runner->addTask(benchmarkTask);
  benchmarkTask.disable(); // Enable for benchmarck
}

void MusicMachine::initFlowerStates()
{
  FlowerState *flowerState;

  int pIds[NUMBER_OF_FLOWERS] = FLOWER_PEER_IDS;
  int bpIds[NUMBER_OF_FLOWERS] = BRANCH_PEER_IDS;

  Track *track;
  list<Track *>::iterator it;

  uint8_t i = 0;

  for (it = tracker->tracks.begin(); it != tracker->tracks.end(); ++it)
  {
    flowerStates[i] = new FlowerState();
    flowerStates[i]->delegate = this;
    flowerStates[i]->track = *it;
    flowerStates[i]->trackType = (TrackerFactory::TrackType)i;
    flowerStates[i]->peerId = pIds[i];
    flowerStates[i]->branchPeerId = bpIds[i];
    i++;
  }
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
    Serial.println("PING");
    break;
  }
  case BENCHMARK_MESSAGE:
  {
    BenchmarkMessage msg;
    memcpy(&msg, incomingData, sizeof(BenchmarkMessage));
    unsigned long deltaTime = micros() - msg.time;
    Serial.printf("R Benchmark time %i %i\n", msg.time, deltaTime);
    break;
  }
  default:
    break;
  }
}

void MusicMachine::trackerBarTick()
{
  int rndInx = random(0, NUMBER_OF_FLOWERS);
  FlowerState *flowerState = flowerStates[rndInx];

  list<Track *>::iterator it = tracker->tracks.begin();
  for (uint8_t i = 0; i < rndInx; i++)
  {
    it++;
  }

  Track *track = *it;

  if (flowerState->state == SILENT)
  {
    flowerState->decreaseCallingCountDown();

    if (flowerState->state == CALLING)
    {
      flowerState->silentCountDown = random(4, 32); // change to random
      flowerState->callingCountDown = random(1, 4); // change to random
    }
  }

  for (uint8_t i = 0; i < NUMBER_OF_FLOWERS; i++)
  {
    flowerState = flowerStates[i];
    flowerState->decreaseSilentCountDown();

    Serial.print(flowerState->state == SILENT ? " - " : " o ");
  }
  Serial.println("");

  //ClockSync message
  unsigned int tickDelay = -1;
  ClockSyncMessage clockMsg;
  clockMsg.tickCounter = tracker->clock->tickCounter + tickDelay;
  clockMsg.bpm = tracker->clock->getBpm();
  SerialMessengerSingleton->sendMessage(&clockMsg, sizeof(ClockSyncMessage));
}

void MusicMachine::flowerStateChanged(FlowerState *flowerState, FlowerStates state)
{
  Serial.printf("peerId: %i state:%i\n", flowerState->peerId, flowerState->state);
  if (state == CALLING)
  {
    flowerState->seed = millis();
    randomSeed(flowerState->seed);
    flowerState->track->radomize();
    flowerState->track->play();

    FlowerCallMessage msg;
    msg.seed = flowerState->seed;
    msg.sourceId = 1;
    msg.trackType = flowerState->trackType;
    msg.targetId = flowerState->peerId;
    SerialMessengerSingleton->sendMessage(&msg, sizeof(FlowerCallMessage));
    msg.targetId = flowerState->branchPeerId;
    SerialMessengerSingleton->sendMessage(&msg, sizeof(FlowerCallMessage));
  }
  else if (state == SILENT)
  {
    flowerState->track->stop();

    FlowerSilentMessage msg;
    msg.seed = flowerState->seed;
    msg.sourceId = 1;
    msg.targetId = flowerState->peerId;
    SerialMessengerSingleton->sendMessage(&msg, sizeof(FlowerSilentMessage));
    msg.targetId = flowerState->branchPeerId;
    SerialMessengerSingleton->sendMessage(&msg, sizeof(FlowerSilentMessage));
  }
}