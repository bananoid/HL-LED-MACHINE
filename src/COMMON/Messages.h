#pragma once

#define BASE_MESSAGE_TYPES PING

// Each message is defined per board.
// Each board can listen and send different type of messages
// A message is defined by the board that generates (e.g. sensor) or display (e.g. leds) the data

// FLOWER messages:
#define FLOWER_MESSAGE_TYPES FLOWER_TOUCH, FLOWER_LED

// SOLENOID messages:
#define SOLENOID_MESSAGE_TYPES SOLENOID_STATE

enum MessageTypes
{
  BASE_MESSAGE_TYPES,
  FLOWER_MESSAGE_TYPES,
  SOLENOID_MESSAGE_TYPES
};

struct BaseMessage
{
  uint8_t messageType = PING;

  // a targeted message is meant to be received by a single board id. use id=0 to broadcast
  uint targetId = 0;
  uint sourceId = 0;
};

struct FlowerTouch : public BaseMessage
{ 
  uint8_t messageType = FLOWER_TOUCH;
};

struct FlowerLed : public BaseMessage
{ 
  uint8_t messageType = FLOWER_LED;
};

struct SolenoidState : public BaseMessage
{ 
  uint8_t messageType = SOLENOID_STATE;
};
