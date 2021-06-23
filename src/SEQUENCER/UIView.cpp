#include "UIView.h"

UIView::UIView()
{
}
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
void UIView::build()
{
}
void UIView::draw()
{
}

void UIView::addChild(UIView *view)
{
  view->parent = this;
  view->ctx = ctx;
  childs.push_back(view);
  view->build();
}