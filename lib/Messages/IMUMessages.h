#pragma once

#include "BaseMessages.h"

#define CONTROL_MESSAGE_TYPES CONTROL_BUTTON_PRESS_MSG, CONTROL_BUTTON_RELEASE_MSG, CONTROL_VALUE_MSG

namespace Messages
{

  enum ControlMessages
  {
    CONTROL_MESSAGE_TYPES
  };

  struct ControlMsg : public Message
  {
    uint8_t channel;
    uint8_t id;
  };

  struct ControlButtonPress : public ControlMsg
  {
    ControlButtonPress()
    {
      type = CONTROL_BUTTON_PRESS_MSG;
    }
  };

  struct ControlButtonRelease : public ControlMsg
  {
    ControlButtonRelease()
    {
      type = CONTROL_BUTTON_RELEASE_MSG;
    }
  };

  struct ControlValue : public ControlMsg
  {
    ControlValue()
    {
      type = CONTROL_VALUE_MSG;
    }
    float value;
  };

} // namespace Messages