#pragma once
#include "UIView.h"
#include <vector>

using namespace std;

class UINavigation
{
public:
  vector<UIView *> viewStack;
  UINavigation();
  void pushView(UIView *view);
  void popView();
};