#include "UIView.h"

void UIView::show()
{
  ctx->pushOffset(frame);
  update();
  draw();

  if (isFocused)
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