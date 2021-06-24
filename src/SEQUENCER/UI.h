#pragma once

#include <Encoder.h>
#include <Bounce2.h>

#define ENCODER_LEFT_PIN_SW 2
#define ENCODER_LEFT_PIN_A 3
#define ENCODER_LEFT_PIN_B 4
#define ENCODER_RIGHT_PIN_SW 30
#define ENCODER_RIGHT_PIN_A 31
#define ENCODER_RIGHT_PIN_B 32

#define NUM_SCREEN_BTN 4
#define SCREEN_BTN_PINS \
  {                     \
    23, 22, 19, 18      \
  }

#define FRONT_LEFT_BTN_PIN 41
#define FRONT_LEFT_LED_PIN 40
#define FRONT_RIGHT_BTN_PIN 39
#define FRONT_RIGHT_LED_PIN 38

#include <Tracker.h>
using namespace HLMusicMachine;

#include "UIView.h"
#include "UITracksView.h"

#include "UIViewController.h"

class UIDelegate
{
public:
  virtual void frontLeftButtonClick();
};

class UI : public UIViewController
{
private:
public:
  UIDelegate *delegate;

  Encoder *leftEncoder;
  Bounce2::Button *leftEncoderButton;

  Encoder *rightEncoder;
  Bounce2::Button *rightEncoderButton;

  const uint8_t screenBtnPins[NUM_SCREEN_BTN] = SCREEN_BTN_PINS;
  Bounce *screenBtns[NUM_SCREEN_BTN];

  Bounce2::Button *frontLeftButton;
  Bounce2::Button *frontRightButton;

  UITracksView *tracksView;

  Tracker *tracker;
  void init(Scheduler *runner, Tracker *tracker);
  void update() override;
  UIView *initRootView() override;
};

extern UI *ui;