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
  return new UIRootView(tracker);
}

void UI::update()
{
  UIViewController::update();

  if (buttonKeys[KEY_ID_FRONT_LEFT]->released())
  {
    tracker->clock->playStop();
  }
}

void UI::saveProject()
{
  ProjectStore projectStore;

  int i = 0;
  for (auto track : tracker->tracks)
  {
    memcpy(&projectStore.trackParams[i], &track->sequencers[0]->parameters, sizeof(Parameters));
    projectStore.tracksEnabled[i] = track->isPlaying;

    i++;
  }

  storage->projectsBank->saveSlot((uint8_t *)&projectStore, sizeof(ProjectStore));
}

void UI::loadProject()
{
  ProjectStore projectStore;
  storage->projectsBank->loadSlot((uint8_t *)&projectStore, sizeof(ProjectStore));

  int i = 0;
  for (auto track : tracker->tracks)
  {
    memcpy(&track->sequencers[0]->parameters, &projectStore.trackParams[i], sizeof(Parameters));

    // Load track enabled/disabled
    projectStore.tracksEnabled[i] ? track->play() : track->stop();

    i++;
  }
}

UI *ui = new UI();