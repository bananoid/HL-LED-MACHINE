#ifndef HL_SRC_SEQUENCER_UIPAGEVIEW
#define HL_SRC_SEQUENCER_UIPAGEVIEW
#include "UIView.h"
#include <vector>
class UIPageView : public UIView
{
private:
  int pageInx = 0;

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

    auto currentView = pages[(uint16_t)pageInx];
    currentView->show();

    ctx->popOffset(frame);
  }

  void focusPrev() override
  {
    pageInx = (pageInx + 1) % pages.size();
  };
  void focusNext() override
  {
    pageInx = (pageInx - 1 + pages.size()) % pages.size();
  };
  void focusChild() override
  {
    ctx->controller->focusView = pages[(uint16_t)pageInx];
    Serial.println("Focus Child");
  }

  void update() override
  {
    // auto wheelSpeed = ctx->controller->wheelEncoders[WHEEL_ID_RIGHT]->speed;
    // if (!ctx->controller->buttonKeys[KEY_ID_WHEEL_RIGHT]->isPressed())
    // {
    //   wheelSpeed /= 4.0;
    // }
    // if (wheelSpeed != 0)
    // {
    //   auto bpm = tracker->clock->getBpm();
    //   tracker->clock->setBpm(bpm + wheelSpeed);
    // }
  }
  void draw() override
  {
  }
};

#endif /* HL_SRC_SEQUENCER_UIPAGEVIEW */
