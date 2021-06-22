#pragma once
#include <Arduino.h>

#include "UIDisplayConfig.h"

#include <vector>
using namespace std;

struct Rect
{
  int x = 0;
  int y = 0;
  int w = 32;
  int h = 16;
};

class UIView
{
public:
  Display *ctx = nullptr;
  Color color;
  Rect frame;
  String label;
  vector<UIView *> childs;
  UIView *parent;
  UIView();
  void show();
  virtual void build();
  virtual void draw();
  void addChild(UIView *view);
};
