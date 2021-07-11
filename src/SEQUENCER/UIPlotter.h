#pragma once
#include "UIView.h"
class UIPlotter : public UIView
{
private:
public:
  float scale = 2;
  enum Direction
  {
    HORIZONTAL,
    VERTICAL,
  };

  Direction direction = VERTICAL;
};
