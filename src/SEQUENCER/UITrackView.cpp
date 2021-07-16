#include "UITrackView.h"

#include "UI.h"

void UITrackView::update()
{
  if (ctx->controller->buttonKeys[KEY_ID_SCREEN_A]->pressed())
  {
    track->togglePlayStop();
  }

  if (ctx->controller->buttonKeys[KEY_ID_SCREEN_B]->pressed())
  {
    focusIn(1);
  }

  if (!storeSlot->isFocused())
  {
    if (ctx->controller->buttonKeys[KEY_ID_SCREEN_C]->pressed())
    {
      setFocusIndex(0);
      setFocus();
    }
    if (ctx->controller->buttonKeys[KEY_ID_SCREEN_D]->pressed())
    {
      focusIn(2);
    }
  }
  else
  {
    // Save slot
    if (ctx->controller->buttonKeys[KEY_ID_SCREEN_C]->pressed())
    {
      ui->saveTrackToSlot(track, storage->tracksBank->currentSlot);
    }
    // Load slot
    if (ctx->controller->buttonKeys[KEY_ID_SCREEN_D]->pressed())
    {
      ui->loadTrackFromSlot(track, storage->tracksBank->currentSlot);
    }
  }

  if (plotter->isFocused())
  {
    auto rightWheelSpeed = ctx->controller->wheelEncoders[WHEEL_ID_RIGHT]->speed;
    if (rightWheelSpeed != 0)
    {
      plotter->setScaleFactor(plotter->scaleFactor + rightWheelSpeed);
    }
  }
}