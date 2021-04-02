#pragma once

#include <BaseMessages.h>
#include <Sequencer.h>

// Each message is defined per board.
// Each board can listen and send different type of messages
// A message is defined by the board that generates (e.g. sensor) or display (e.g. leds) the data

// FLOWER messages:
#define FLOWER_MESSAGE_TYPES FLOWER_ACTIVATION, FLOWER_STATE, FLOWER_EXPLOSION, FLOWER_GYRO

// BRANCH messages:
#define BRANCH_MESSAGE_TYPES BRANCH_STATE

// TREE messages:
#define TREE_MESSAGE_TYPES TREE_STATE

// ROCK messages:
#define ROCK_MESSAGE_TYPES ROCK_BPM

#define CLOCK_TYPES CLOCK_SYNC

using namespace Messages;
using namespace HLMusicMachine;

enum MessageTypes
{
  BASE_MESSAGE_TYPES,
  FLOWER_MESSAGE_TYPES,
  BRANCH_MESSAGE_TYPES,
  ROCK_MESSAGE_TYPES,
  TREE_MESSAGE_TYPES,
  CLOCK_TYPES
};

struct FlowerGyroMessage : public BaseMessage
{
  FlowerGyroMessage()
  {
    type = FLOWER_GYRO;
  }
};

struct FlowerActivationMessage : public BaseMessage
{
  FlowerActivationMessage()
  {
    type = FLOWER_ACTIVATION;
  }
  float activation = 0;
};

struct FlowerStateMessage : public BaseMessage
{
  FlowerStateMessage()
  {
    type = FLOWER_STATE;
  }

  uint8_t state = 0;
};

struct ClockSyncMessage : public BaseMessage
{
  ClockSyncMessage()
  {
    type = CLOCK_SYNC;
  }
  uint32_t tickCounter = 0;
  float bpm = 120;
};