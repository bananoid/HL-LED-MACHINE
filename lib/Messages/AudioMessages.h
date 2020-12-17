#pragma once

#include "BaseMessages.h"

#define AUDIO_MESSAGE_TYPES AUDIO_MESSAGE_SIGNALS

namespace Messages
{
  enum AudioMessages
  {
    AUDIO_MESSAGE_TYPES
  };

  struct AudioSignalsMsg : public Message
  {
    AudioSignalsMsg()
    {
      type = AUDIO_MESSAGE_SIGNALS;
    }
    float lowBand;
    float midBand;
    float hiBand;
  };
} // namespace Messages