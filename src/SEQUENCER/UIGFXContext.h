#pragma once

#include "UIDisplayConfig.h"
#include <GFXUtils.h>
#include <Arduino.h>
#include "UIViewController.h"
#include "GFX_fonts/Font5x7FixedMono.h"

using namespace GFX;

static const uint8_t ALIGN_LEFT = 0;
static const uint8_t ALIGN_CENTER = 1;
static const uint8_t ALIGN_RIGHT = 2;

#define BG_INT 50
#define MD_INT 80

static const Color COLOR_WHITE_F = Color(255, 255, 255);
static const Color COLOR_WHITE_B = Color(BG_INT, BG_INT, BG_INT);
static const Color COLOR_BLACK_F = Color(10, 10, 10);
static const Color COLOR_BLACK_B = Color(0, 0, 0);
static const Color COLOR_RED_F = Color(255, 0, 0);
static const Color COLOR_RED_B = Color(BG_INT, 0, 0);
static const Color COLOR_GREEN_F = Color(0, 255, 0);
static const Color COLOR_GREEN_B = Color(0, BG_INT, 0);
static const Color COLOR_BLUE_F = Color(0, 0, 255);
static const Color COLOR_BLUE_B = Color(0, 0, 255);
static const Color COLOR_CYAN_F = Color(0, 255, 255);
static const Color COLOR_CYAN_M = Color(0, MD_INT, MD_INT);
static const Color COLOR_CYAN_B = Color(0, BG_INT, BG_INT);
static const Color COLOR_MAGENTA_F = Color(255, 0, 255);
static const Color COLOR_MAGENTA_B = Color(BG_INT, 0, BG_INT);
static const Color COLOR_YELLOW_F = Color(255, 255, 0);
static const Color COLOR_YELLOW_B = Color(BG_INT, BG_INT, 0);

class UIViewController;
class UIGFXContext : public Print
{
public:
  Display *display;
  UIViewController *controller;

  Point offset = {0, 0};

#ifdef DEBUG_VIEW_TREE
  int pushCount = 0;
#endif //DEBUG_VIEW_TREE

  UIGFXContext()
  {
    display = new Display();
    display->begin();
    display->setTextWrap(false);
    setFont(Font5x7FixedMono);
  }

  void pushOffset(const Point offset)
  {
    this->offset.x += offset.x;
    this->offset.y += offset.y;
  }

  void pushOffset(Rect frame)
  {
    pushOffset({frame.x, frame.y});
  }

  void popOffset(const Point offset)
  {
    this->offset.x -= offset.x;
    this->offset.y -= offset.y;
  }

  void popOffset(const Rect frame)
  {
    popOffset({frame.x, frame.y});
  }

  void clear()
  {
    display->fillScreen({10, 50, 40});
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

  void drawCircle(Rect frame, const Color color, bool fill = false)
  {
    if (fill)
    {
      display->fillCircle(offset.x + frame.x, offset.y + frame.y, frame.w, color);
    }
    else
    {
      display->drawCircle(offset.x + frame.x, offset.y + frame.y, frame.w, color);
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

  Rect clippingBounds = {0, 0, 0, 0};
  void setClippingBounds(Rect bounds)
  {
    clippingBounds = {bounds.x,
                      bounds.y,
                      bounds.w,
                      bounds.h};
    display->setBounds({
        clippingBounds.x,
        clippingBounds.y,
        clippingBounds.w,
        clippingBounds.h,
    });
  }

  // void resetBounds()
  // {
  //   display->resetBounds();
  // }

  Rect pushClippingBounds(const Rect bounds)
  {
    clippingBounds = clippingBounds.interserctWith(
        {bounds.x + offset.x,
         bounds.y + offset.y,
         bounds.w,
         bounds.h});

    if (clippingBounds.w > 0 && clippingBounds.h > 0)
    {
      display->setBounds({clippingBounds.x,
                          clippingBounds.y,
                          clippingBounds.w,
                          clippingBounds.h});

      // Debuging Clipping Bounds
      // display->drawRect(clippingBounds.x,
      //                   clippingBounds.y,
      //                   clippingBounds.w,
      //                   clippingBounds.h, {0, 255, 0});
    }

    return clippingBounds;
  }
  void popClippingBounds(const Rect bounds)
  {
    clippingBounds = bounds;
    display->setBounds({bounds.x, bounds.y, bounds.w, bounds.h});
  }
};
