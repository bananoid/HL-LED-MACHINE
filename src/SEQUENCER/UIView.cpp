#include "UIView.h"

void UIView::show()
{
  ctx->pushOffset(frame);
  draw();
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