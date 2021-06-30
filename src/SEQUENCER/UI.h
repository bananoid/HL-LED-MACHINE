#pragma once

#include <Encoder.h>
#include <Bounce2.h>

#define FRONT_LEFT_LED_PIN 40
#define FRONT_RIGHT_LED_PIN 38

#include <Tracker.h>
using namespace HLMusicMachine;

#include "UIView.h"
#include "UIPageView.h"
#include "UIClockView.h"
#include "UIHarmonyView.h"
#include "UITracksView.h"

#include "UIViewController.h"

#include "config.h"

const MapIdToButtonConfig buttonsConfig = {
    {KEY_ID_SCREEN_A, {23, INPUT_PULLUP, true}},
    {KEY_ID_SCREEN_B, {22, INPUT_PULLUP, true}},
    {KEY_ID_SCREEN_C, {19, INPUT_PULLUP, true}},
    {KEY_ID_SCREEN_D, {18, INPUT_PULLUP, true}},
    {KEY_ID_FRONT_LEFT, {41, INPUT_PULLUP, false}},
    {KEY_ID_FRONT_RIGHT, {39, INPUT_PULLUP, false}},
    {KEY_ID_WHEEL_LEFT, {2, INPUT, true}},
    {KEY_ID_WHEEL_RIGHT, {30, INPUT, true}},
};

const MapIdToEncoderConfig encodersConfig = {
    {WHEEL_ID_LEFT, {3, 4}},
    {WHEEL_ID_RIGHT, {31, 32}},
};

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

  Tracker *tracker;
  void init(Scheduler *runner, Tracker *tracker);
  void update() override;
  UIView *initRootView() override;
};

extern UI *ui;