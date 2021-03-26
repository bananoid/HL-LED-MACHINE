#pragma once

#include <BaseMessages.h>

#define BASE_MESSAGE_TYPES PING, MSG_AUDIO_BANDS

// Each message is defined per board.
// Each board can listen and send different type of messages
// A message is defined by the board that generates (e.g. sensor) or display (e.g. leds) the data

// FLOWER messages:
#define FLOWER_MESSAGE_TYPES

using namespace Messages;

enum MessageTypes
{
  BASE_MESSAGE_TYPES,
  FLOWER_MESSAGE_TYPES
};

struct AudioBandsMessage : public BaseMessage
{
  AudioBandsMessage()
  {
    type = MSG_AUDIO_BANDS;
  }

  float bandLowVal = 0;
  float bandMidVal = 0;
  float bandHighVal = 0;
};
