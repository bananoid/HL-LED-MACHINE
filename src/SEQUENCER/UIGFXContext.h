#pragma once

#include "UIDisplayConfig.h"
#include <GFXUtils.h>

using namespace GFX;

// #define  DEBUG_VIEW_TREE

class UIGFXContext
{
public:
  Display *display;
  struct Offset
  {
    int x = 0;
    int y = 0;
  };

  Offset offset = {0, 0};

#ifdef DEBUG_VIEW_TREE
  int pushCount = 0;
#endif //DEBUG_VIEW_TREE

  UIGFXContext()
  {
    display = new Display();
    display->begin();
  }

  void pushOffset(Rect frame)
  {
    offset.x += frame.x;
    offset.y += frame.y;

#ifdef DEBUG_VIEW_TREE
    if (pushCount == 0)
    {
      Serial.println("");
    }

    for (int i = 0; i < pushCount; i++)
    {
      Serial.print("|   ");
    }

    Serial.printf("d:[x %i y %i] - o:[x %i y %i] \n", frame.x, frame.y, offset.x, offset.y);

    pushCount++;
#endif //DEBUG_VIEW_TREE
  }

  void popOffset(Rect frame)
  {
    offset.x -= frame.x;
    offset.y -= frame.y;

#ifdef DEBUG_VIEW_TREE
    pushCount--;
#endif //DEBUG_VIEW_TREE
  }

  void clear()
  {
    display->fillScreen({0, 0, 0});
  }
  void commit()
  {
    display->updateScreen();
  }

  void drawRect(Rect frame, fRGB color, bool fill = false)
  {
    ssd1351::RGB c = {color.r * 255, color.g * 255, color.b * 255};
    if (fill)
    {
      display->fillRect(offset.x + frame.x, offset.y + frame.y, frame.w, frame.h, c);
    }
    else
    {
      display->drawRect(offset.x + frame.x, offset.y + frame.y, frame.w, frame.h, c);
    }
  }

  void setFont(const GFXfont &new_font)
  {
    display->setFont(new_font);
  }

  void setTextSize(uint8_t new_size)
  {
    setTextSize(new_size);
  }

  void setTextColor(fRGB color)
  {
    setTextColor({color.r * 255, color.g * 255, color.b * 255});
  }

  void setCursor(int16_t x, int16_t y)
  {
    setCursor(x, y);
  }

  // void print(){

  // }
};
