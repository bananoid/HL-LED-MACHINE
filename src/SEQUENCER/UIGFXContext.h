#pragma once

#include "UIDisplayConfig.h"
#include <GFXUtils.h>
#include <Arduino.h>

using namespace GFX;

// #define  DEBUG_VIEW_TREE

static const uint8_t ALIGN_LEFT = 0;
static const uint8_t ALIGN_CENTER = 1;
static const uint8_t ALIGN_RIGHT = 2;

static const Color COLOR_WHITE_F = Color(255, 255, 255);
static const Color COLOR_WHITE_B = Color(100, 100, 100);
static const Color COLOR_BLACK_F = Color(10, 10, 10);
static const Color COLOR_BLACK_B = Color(0, 0, 0);
static const Color COLOR_RED_F = Color(255, 0, 0);
static const Color COLOR_RED_B = Color(100, 0, 0);
static const Color COLOR_GREEN_F = Color(0, 255, 0);
static const Color COLOR_GREEN_B = Color(0, 100, 0);
static const Color COLOR_BLUE_F = Color(0, 0, 255);
static const Color COLOR_BLUE_B = Color(0, 0, 255);
static const Color COLOR_CYAN_F = Color(0, 255, 255);
static const Color COLOR_CYAN_B = Color(0, 100, 100);
static const Color COLOR_MAGENTA_F = Color(255, 0, 255);
static const Color COLOR_MAGENTA_B = Color(100, 0, 100);
static const Color COLOR_YELLOW_F = Color(255, 255, 0);
static const Color COLOR_YELLOW_B = Color(100, 100, 0);

class UIGFXContext : public Print
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

  void drawRect(Rect frame, const Color color, bool fill = false)
  {
    if (fill)
    {
      display->fillRect(offset.x + frame.x, offset.y + frame.y, frame.w, frame.h, color);
    }
    else
    {
      display->drawRect(offset.x + frame.x, offset.y + frame.y, frame.w, frame.h, color);
    }
  }

  void setFont(const GFXfont &new_font)
  {
    display->setFont(new_font);
  }

  void setTextSize(uint8_t new_size)
  {
    display->setTextSize(new_size);
  }

  void setTextColor(const Color color)
  {
    display->setTextColor(color);
  }

  void setCursor(int16_t x, int16_t y)
  {
    display->setCursor(offset.x + x, offset.y + y);
  }

  size_t write(uint8_t c)
  {
    return display->write(c);
  }

  void drawText(String str, int16_t x, int16_t y, uint8_t align = ALIGN_LEFT)
  {
    display->drawText(str.c_str(), offset.x + x, offset.y + y, align);
  }
};
