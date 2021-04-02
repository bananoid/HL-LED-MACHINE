#include "MusicMachine.h"

#include "AOYAMA_TREE/COMMON/Messages.h"
#include "AOYAMA_TREE/COMMON/TrackerFactory.h"

using namespace HLMusicMachine;

MusicMachine::MusicMachine(Scheduler *runner)
{
  randomSeed(analogRead(0));

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

  // update frame
  updateFrameTask.set(16 * TASK_MILLISECOND, TASK_FOREVER, [this]() {
    // update
    for (int i = 0; i < NUMBER_OF_FLOWERS; i++)
    {
      flowerStates[i]->updateWithFrame();
    }
  });
  runner->addTask(updateFrameTask);
  updateFrameTask.enable();
}

void MusicMachine::initFlowerStates()
{
  int pIds[NUMBER_OF_FLOWERS] = FLOWER_PEER_IDS;
  int bpIds[NUMBER_OF_FLOWERS] = BRANCH_PEER_IDS;

  list<Track *>::iterator it;

  uint8_t i = 0;

  for (it = tracker->tracks.begin(); it != tracker->tracks.end(); ++it)
  {
    flowerStates[i] = new FlowerState();
    flowerStates[i]->delegate = this;
    flowerStates[i]->track = *it;
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
  case FLOWER_ACTIVATION:
  {
    FlowerActivationMessage msg;
    memcpy(&msg, incomingData, sizeof(FlowerActivationMessage));
    FlowerState *flowerState = FlowerState::getFlowerStateByPeerId(msg.sourceId, flowerStates, NUMBER_OF_FLOWERS);

    if (flowerState != nullptr)
    {
      // Serial.printf("Flower peerId %i Activation %f\n", flowerState->peerId, msg.activation);

      flowerState->activation = msg.activation;
      if (flowerState->state != SILENT)
      {
      }
    }
  }
  default:
    break;
  }
}

void MusicMachine::trackerBarTick()
{
  for (int i = 0; i < NUMBER_OF_FLOWERS; i++)
  {
    FlowerState *flowerState = flowerStates[i];
    flowerState->updateWithBar();
    Serial.print(flowerState->state == SILENT ? " ------------- " : " [" + String(flowerState->peerId) + "][" + String(flowerState->state) + "][A" + String(flowerState->activation) + "] ");
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
  FlowerStateMessage msg;
  msg.targetId = flowerState->peerId;
  msg.state = state;
  SerialMessengerSingleton->sendMessage(&msg, sizeof(FlowerStateMessage));
}

void MusicMachine::flowerExplode(){};