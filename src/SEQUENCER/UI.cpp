#include "UI.h"

#include <Arduino.h>
#include <SPI.h>
#include <SequencerParameters.h>

using namespace HLMusicMachine;

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

void UI::saveTrackToSlot(Track *track, uint16_t slot)
{
  Parameters params;
  memcpy(&params, &track->sequencers[0]->parameters, sizeof(Parameters));
  storage->tracksBank->saveSlot((uint8_t *)&params, sizeof(Parameters), slot);
  // Serial.printf("save to Track inx %i\n", trackInx);
};

void UI::saveTrackToSlot(uint8_t trackInx, uint16_t slot)
{
  if (trackInx >= tracker->tracks.size())
  {
    return;
  }
  auto track = tracker->tracks[trackInx];
  saveTrackToSlot(track, slot);
}

void UI::loadTrackFromSlot(Track *track, uint16_t slot)
{
  Parameters params;
  storage->tracksBank->loadSlot((uint8_t *)&params, sizeof(Parameters), slot);
  memcpy(&track->sequencers[0]->parameters, &params, sizeof(Parameters));
  // Serial.printf("load to Track inx %i\n", trackInx);
};

void UI::loadTrackFromSlot(uint8_t trackInx, uint16_t slot)
{
  if (trackInx >= tracker->tracks.size())
  {
    return;
  }
  auto track = tracker->tracks[trackInx];
  loadTrackFromSlot(track, slot);
}

UI *ui = new UI();