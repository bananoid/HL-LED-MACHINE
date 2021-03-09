#pragma once

#include <BaseMessages.h>
#include <ControlMessages.h>
#include <AudioMessages.h>

using namespace Messages;

struct LEDShaderSynthState
{
  float scale = 1.f;
  float speed = 1.f;

  float que = 2.3f;
  float sym = 0.9f;
  float fmAmo = 4.f;
  float fmFrq = 1.f;

  float hue = 0.55f;
  float hueRad = 0.1f;
  // float hueSpeed = 2.f;
};

#define LED_SYNT_MESSAGE_TYPES LED_SYNT_MESSAGE_SHADER_STATE

enum LEDSynthMessages
{
  BASE_MESSAGE_TYPES,
  CONTROL_MESSAGE_TYPES,
  AUDIO_MESSAGE_TYPES,
  LED_SYNT_MESSAGE_TYPES
};

struct LEDSynthStateMsg : public Message
{
  LEDSynthStateMsg()
  {
    type = LED_SYNT_MESSAGE_SHADER_STATE;
  }
  uint8_t stripDestinationInx = 0; // 0 for All Destination
  float interpolationSpeed = 0;    // 0 is immediate
  LEDShaderSynthState layerAState;
  LEDShaderSynthState layerBState;
};
