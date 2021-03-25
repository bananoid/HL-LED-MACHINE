#pragma once

#include <BaseMessages.h>

#define BASE_MESSAGE_TYPES PING

// Each message is defined per board.
// Each board can listen and send different type of messages
// A message is defined by the board that generates (e.g. sensor) or display (e.g. leds) the data

// FLOWER messages:
#define FLOWER_MESSAGE_TYPES FLOWER_TOUCH, FLOWER_GYRO, FLOWER_LED

// BRANCH messages:
#define BRANCH_MESSAGE_TYPES BRANCH_STATE

// TREE messages:
#define TREE_MESSAGE_TYPES TREE_STATE

// ROCK messages:
#define ROCK_MESSAGE_TYPES ROCK_BPM

using namespace Messages;

enum MessageTypes
{
  BASE_MESSAGE_TYPES,
  FLOWER_MESSAGE_TYPES,
  BRANCH_MESSAGE_TYPES,
  ROCK_MESSAGE_TYPES,
  TREE_MESSAGE_TYPES
};

// struct BaseMessage
// {
//   uint8_t messageType = PING;

//   // a targeted message is meant to be received by a single board id. use id=0 to broadcast
//   uint targetId = 0;
//   uint sourceId = 0;
// };

struct FlowerTouchMessage : public BaseMessage
{
  uint8_t messageType = FLOWER_TOUCH;
};

struct FlowerGyroMessage : public BaseMessage
{
  uint8_t messageType = FLOWER_GYRO;
};

struct FlowerLedMessage : public BaseMessage
{
  uint8_t messageType = FLOWER_LED;
};

struct BranchStateMessage : public BaseMessage
{
  uint8_t messageType = BRANCH_STATE;
};

struct TreeStateMessage : public BaseMessage
{
  uint8_t messageType = TREE_STATE;
};
