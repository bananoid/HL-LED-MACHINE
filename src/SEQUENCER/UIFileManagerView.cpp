#include "UIFileManagerView.h"
#include "UI.h"

void UIFileManagerView::update()
{
  if (paramProjectSlot->isFocused())
  {
    focusMode = PROJECTS;

    // Save Project
    if (ctx->controller->buttonKeys[KEY_ID_SCREEN_A]->released())
    {
      currentLoadedProjectSlot = storage->projectsBank->currentSlot;
      Serial.printf("Save Project %i\n", currentLoadedProjectSlot);
      ui->saveProject();
    }
    // Load Project
    else if (ctx->controller->buttonKeys[KEY_ID_SCREEN_D]->released())
    {
      currentLoadedProjectSlot = storage->projectsBank->currentSlot;
      Serial.printf("Load Project %i\n", currentLoadedProjectSlot);
      ui->loadProject();
    }
  }
  else if (paramTracksSlot->isFocused() || paramTrackInx->isFocused())
  {
    focusMode = TRACKS;

    int trackSlot = storage->tracksBank->currentSlot;
    int trackInx = selectedTrack - 1;

    // Save Track
    if (ctx->controller->buttonKeys[KEY_ID_SCREEN_A]->released())
    {
      Serial.printf("Save Track %i to slot %i\n", trackSlot, trackInx);
    }
    // Load Track
    else if (ctx->controller->buttonKeys[KEY_ID_SCREEN_D]->released())
    {
      Serial.printf("Load Track %i from slot %i\n", trackSlot, trackInx);
    }
  }
  else
  {
    focusMode = NONE;
  }
}