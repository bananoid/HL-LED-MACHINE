#pragma once
#include <Arduino.h>

#define BASE_MESSAGE_TYPES PING, BENCHMARK_MESSAGE

namespace Messages
{
  struct BaseMessage
  {
    uint8_t type = 0;
  };

  struct BenchmarkMessage : public BaseMessage
  {
    BenchmarkMessage()
    {
      type = 1;
    }
    unsigned long time;
  };

}
