#include "UI.h"

#include <Arduino.h>
#include <SPI.h>

void UI::init(Scheduler *runner, Tracker *tracker)
{
  this->tracker = tracker;

  initKeys(buttonsConfig);
  initWheels(encodersConfig);

  pinMode(FRONT_LEFT_LED_PIN, OUTPUT);
  pinMode(FRONT_RIGHT_LED_PIN, OUTPUT);

  UIViewController::init(runner);
}

UIView *UI::initRootView()
{
  // auto pageView = new UIScrollView({
  //     new UIClockView(tracker),
  //     new UIHarmonyView(tracker),
  //     new UITracksView(tracker),
  // });
  // return pageView;

  return new UIRootView(tracker);
}

void UI::update()
{
  UIViewController::update();

  if (buttonKeys[KEY_ID_FRONT_LEFT]->released())
  {
    delegate->frontLeftButtonClick();
  }
}

UI *ui = new UI();