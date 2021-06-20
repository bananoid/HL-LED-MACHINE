#pragma once
#include <Arduino.h>

#include "UIDisplayConfig.h"

struct Rect
{
  int x = 0;
  int y = 0;
  int w = 32;
  int h = 16;
};

class UIComponet
{
public:
  Display *ctx;
  Color *color;
  Rect bounds;
  String label;
  virtual void draw();
};
