#include "UIViewController.h"

UIViewController::UIViewController()
{
  this->rootView = getRootView();
}
UIView *UIViewController::getRootView()
{
  return new UIView();
}
void UIViewController::show()
{
  rootView->show();
}