#include "UIView.h"

void UIView::show()
{
  ctx->pushOffset(frame);
  update();
  draw();

  if (isFocused())
  {
    ctx->drawRect({0, 0, frame.w, frame.h}, COLOR_WHITE_F);
  }

  for (UIView *view : childs)
  {
    view->show();
  }
  ctx->popOffset(frame);
}

void UIView::addChild(UIView *view)
{
  view->parent = this;
  view->ctx = ctx;
  childs.push_back(view);
  view->build();
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
void UIView::focusParent()
{
  if (parent != nullptr)
  {
    ctx->controller->focusView = parent;
  }
}

void UIView::focusPrev()
{
  focusIndex = (focusIndex - 1 + childs.size()) % childs.size();
};
void UIView::focusNext()
{
  focusIndex = (focusIndex + 1) % childs.size();
};
void UIView::focusChild()
{
  if (focusIndex >= childs.size() || focusIndex < 0)
  {
    return;
  }
  ctx->controller->focusView = childs[focusIndex];
}