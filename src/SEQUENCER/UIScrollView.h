#pragma once
#include "UIView.h"
#include <vector>
class UIScrollView : public UIView
{
public:
  enum Direction
  {
    HORIZONTAL,
    VERTICAL,
    GRID,
  };

  Direction layoutType = VERTICAL;

  UIScrollView()
  {
  }

  void layout() override
  {
    int pos = 0;
    if (layoutType == HORIZONTAL)
    {
      for (auto it : childs)
      {
        it->frame.y = 0;
        it->frame.x = pos;
        it->frame.h = frame.h;
        pos += it->frame.w;
      }
    }
    else if (layoutType == VERTICAL)
    {
      for (auto it : childs)
      {
        it->frame.x = 0;
        it->frame.y = pos;
        it->frame.w = frame.w;
        pos += it->frame.h;
      }
    }

    layoutChilds();
  }

  void setFocusIndex(uint16_t inx) override
  {
    UIView::setFocusIndex(inx);
    auto currentView = childs[(uint16_t)focusIndex];
    scroll.x = -currentView->frame.x;
    scroll.y = -currentView->frame.y;
  };
};