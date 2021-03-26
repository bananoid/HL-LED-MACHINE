#pragma once
#include <Arduino.h>

// #define BASE_MESSAGE_TYPES NO_MESSAGE, PING

namespace Messages
{

  // enum BaseMessageTypes
  // {
  //   BASE_MESSAGE_TYPES
  // };

  struct BaseMessage
  {
    uint8_t type = 0;
    uint8_t targetId = 0;
    uint8_t sourceId = 0;
  };

} // namespace Messages
