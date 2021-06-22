#include "UINavigation.h"

UINavigation::UINavigation()
{
}
void UINavigation::pushView(UIView *view)
{
  viewStack.push_back(view);
}
void UINavigation::popView()
{
  viewStack.pop_back();
}