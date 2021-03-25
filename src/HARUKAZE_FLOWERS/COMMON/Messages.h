#pragma once

#include <BaseMessages.h>

#define BASE_MESSAGE_TYPES PING

// Each message is defined per board.
// Each board can listen and send different type of messages
// A message is defined by the board that generates (e.g. sensor) or display (e.g. leds) the data

// FLOWER messages:
#define FLOWER_MESSAGE_TYPES FLOWER_LED

using namespace Messages;

enum MessageTypes
{
  BASE_MESSAGE_TYPES,
  FLOWER_MESSAGE_TYPES
};

struct FlowerLedMessage : public BaseMessage
{
  uint8_t messageType = FLOWER_LED;
};
