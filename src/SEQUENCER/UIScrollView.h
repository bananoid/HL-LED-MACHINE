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

  void setFocusIndex(int16_t inx) override
  {
    inx = constrain(inx, 0, childs.size() - 1);
    UIView::setFocusIndex(inx);
    auto currentView = childs[(uint16_t)focusIndex];
    scroll.x = -currentView->frame.x;
    scroll.y = -currentView->frame.y;

    auto lastChild = childs.back();

    auto minScrollX = frame.w - lastChild->frame.x - lastChild->frame.w;
    scroll.x = max(scroll.x, minScrollX);

    auto minScrollY = frame.h - lastChild->frame.y - lastChild->frame.h;
    scroll.y = max(scroll.y, minScrollY);
  };
};