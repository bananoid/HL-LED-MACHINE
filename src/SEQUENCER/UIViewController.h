#pragma once
#include "UIDisplayConfig.h"
#include "UIView.h"
class UIViewController
{
public:
  UIViewController();
  UIView *rootView;
  UIView *getRootView();
  void show();
};