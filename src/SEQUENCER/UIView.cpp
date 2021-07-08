#include "UIView.h"

void UIView::show()
{
  auto clippingBounds = ctx->pushClippingBounds(frame);
  if (clippingBounds.w <= 0 || clippingBounds.h <= 0)
  {
    return;
  }

  ctx->pushOffset(frame);

  //// Debuging frane
  // uint8_t dc = 255 - depht * 80;
  // int padding = depht * 1;
  // ctx->drawRect({padding, padding, frame.w - padding * 2, frame.h - padding * 2}, {dc, dc, dc});

  update();
  draw();

  if (isFocused())
  {
    ctx->drawRect({0, 0, frame.w, frame.h}, focusColor);
  }

  ctx->pushOffset(scroll);
  for (UIView *view : childs)
  {
    view->show();
    ctx->popClippingBounds(clippingBounds);
  }
  ctx->popOffset(scroll);
  ctx->popOffset(frame);
}

UIView *UIView::addChild(UIView *view)
{
  view->parent = this;
  view->depht = depht + 1;
  view->ctx = ctx;
  childs.push_back(view);
  view->build();
  return view;
}

bool UIView::isFocused()
{
  if (this->parent == nullptr)
  {
    return false;
  }
  if (ctx->controller->focusView != this->parent)
  {
    return false;
  }
  return this->parent->childs[this->parent->focusIndex] == this;
}

void UIView::setFocusIndex(int16_t inx)
{
  focusIndex = constrain(inx, 0, childs.size() - 1);
}
void UIView::focusPrev()
{
  if (loopFocusSelection)
  {
    setFocusIndex((focusIndex - 1 + childs.size()) % childs.size());
  }
  else
  {
    setFocusIndex(focusIndex - 1);
  }
};
void UIView::focusNext()
{
  if (loopFocusSelection)
  {
    setFocusIndex((focusIndex + 1) % childs.size());
  }
  else
  {
    setFocusIndex(focusIndex + 1);
  }
};

UIView *UIView::getSubView()
{
  return nullptr;
};

void UIView::focusOut()
{
  if (parent != nullptr)
  {
    ctx->controller->focusView = parent;
  }
  else
  {
    ctx->controller->popView();
  }
}
void UIView::focusIn()
{
  if (focusIndex >= childs.size() || focusIndex < 0)
  {
    return;
  }

  auto subView = childs[focusIndex]->getSubView();

  if (subView != nullptr)
  {
    ctx->controller->pushView(subView);
  }

  if (childs[focusIndex]->childs.size() == 0)
  {
    return;
  }

  ctx->controller->focusView = childs[focusIndex];
}

void UIView::layoutChilds()
{
  for (auto it : childs)
  {
    it->layout();
  }
};

void UIView::layout()
{
  layoutChilds();
}
