#pragma once
#include <Arduino.h>

#define BASE_MESSAGE_TYPES NO_MESSAGE

namespace Messages
{

  enum BaseMessageTypes
  {
    BASE_MESSAGE_TYPES
  };

  struct Message
  {
    uint8_t type = NO_MESSAGE;
  };

} // namespace Messages
