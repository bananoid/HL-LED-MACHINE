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
      ui->saveProject();
    }
    // Load Project
    else if (ctx->controller->buttonKeys[KEY_ID_SCREEN_D]->released())
    {
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
      // Serial.printf("Save Track %i to slot %i\n", trackSlot, trackInx);
      ui->saveTrackToSlot(trackInx, trackSlot);
    }
    // Load Track
    else if (ctx->controller->buttonKeys[KEY_ID_SCREEN_D]->released())
    {
      // Serial.printf("Load Track %i from slot %i\n", trackSlot, trackInx);
      ui->loadTrackFromSlot(trackInx, trackSlot);
    }
  }
  else
  {
    focusMode = NONE;
    // Save Track
    if (ctx->controller->buttonKeys[KEY_ID_SCREEN_A]->released())
    {
      if (ui->autoSaveTask.isEnabled())
      {
        ui->autoSaveTask.disable();
        autoSaveEnabled = false;
      }
      else
      {
        ui->autoSaveTask.enable();
        autoSaveEnabled = true;
      }
    }
    // Load Track
    else if (ctx->controller->buttonKeys[KEY_ID_SCREEN_D]->released())
    {
      ui->loadAutoSave();
    }
  }
}