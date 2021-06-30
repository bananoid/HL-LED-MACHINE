#ifndef HL_SRC_SEQUENCER_UIPAGEVIEW
#define HL_SRC_SEQUENCER_UIPAGEVIEW
#include "UIView.h"
#include <vector>
class UIPageView : public UIView
{
public:
  vector<UIView *> pages;
  UIPageView(const vector<UIView *> pages)
  {
    this->pages = pages;
  }
  // void addChild(UIView *view, int position){
  // }
  void build() override
  {
    for (auto page : pages)
    {
      page->frame = frame;
      addChild(page);
    }
  }

  void show() override
  {
    ctx->pushOffset(frame);
    update();
    draw();

    auto currentView = pages[(uint16_t)focusIndex];
    currentView->show();

    ctx->popOffset(frame);
  }

  void update() override
  {
  }
  void draw() override
  {
  }
};

#endif /* HL_SRC_SEQUENCER_UIPAGEVIEW */
