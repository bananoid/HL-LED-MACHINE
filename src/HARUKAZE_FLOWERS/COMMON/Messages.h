#pragma once

#include <BaseMessages.h>

#define BASE_MESSAGE_TYPES PING,                      \
                           MSG_AUDIO_BANDS,           \
                           MSG_LED_SYNTH_LAYER,       \
                           MSG_LED_SYNTH_LAYER_COLOR, \
                           MSG_LED_SYNTH_LAYER_SHAPE, \
                           MSG_LED_SYNTH_LAYER_AUDIO, \
                           MSG_LED_SYNTH_GLOBAL

// Each message is defined per board.
// Each board can listen and send different type of messages
// A message is defined by the board that generates (e.g. sensor) or display (e.g. leds) the data

// FLOWER messages:
// #define FLOWER_MESSAGE_TYPES

using namespace Messages;

enum MessageTypes
{
  BASE_MESSAGE_TYPES
  // FLOWER_MESSAGE_TYPES
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

struct LedSynthLayerMessage : public BaseMessage
{
  LedSynthLayerMessage()
  {
    type = MSG_LED_SYNTH_LAYER;
  };

  float que = 2.3f;
  float sym = 0.9f;
  float fmAmo = 4.f;
  float fmFrq = 1.f;

  float hue = 0.55f;
  float hueRad = 0.1f;
  float scale = 1.f;
  float speed = 1.f;

  float audioInfluenceLowBand = 1;
  float audioInfluenceMidBand = 1;
  float audioInfluenceHighBand = 1;

  float intensity = 1; // brightness
  uint8_t layer = 0;
};

struct LedSynthLayerColorMessage : public BaseMessage
{
  LedSynthLayerColorMessage()
  {
    type = MSG_LED_SYNTH_LAYER_COLOR;
  };

  float hue = 0.55f;
  float hueRad = 0.1f;
  float scale = 1.f;
  float speed = 1.f;

  float intensity = 1; // brightness
  uint8_t layer = 0;
};

struct LedSynthLayerShapeMessage : public BaseMessage
{
  LedSynthLayerShapeMessage()
  {
    type = MSG_LED_SYNTH_LAYER_SHAPE;
  };

  float que = 2.3f;
  float sym = 0.9f;
  float fmAmo = 4.f;
  float fmFrq = 1.f;

  uint8_t layer = 0;
};

struct LedSynthLayerAudioMessage : public BaseMessage
{
  LedSynthLayerAudioMessage()
  {
    type = MSG_LED_SYNTH_LAYER_AUDIO;
  };

  float audioInfluenceLowBand = 1;
  float audioInfluenceMidBand = 1;
  float audioInfluenceHighBand = 1;

  uint8_t layer = 0;
};

struct LedSynthGlobalMessage : public BaseMessage
{
  LedSynthGlobalMessage()
  {
    type = MSG_LED_SYNTH_GLOBAL;
  };
  float saturation = 1.0f;
  float interpolationSpeed = 0;
  float audioFilterSpeed = 0;

  float globalIntensity = 1;
};
