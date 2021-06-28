#pragma once
#include <Arduino.h>

#include "UIGFXContext.h"
#include <GFXUtils.h>
using namespace GFX;

#include <vector>
using namespace std;

class UIView
{
public:
  UIGFXContext *ctx = nullptr;
  Rect frame = {0, 0, 16, 16};
  String label;
  vector<UIView *> childs;
  UIView *parent;
  UIView(){};
  void show();
  virtual void build(){};
  virtual void update(){};
  virtual void draw(){};
  void addChild(UIView *view);

  bool isFocused = false;
  virtual void onKeyPress(uint16_t id) { parent->onKeyPress(id); };
  virtual void onKeyRelease(uint16_t id) { parent->onKeyRelease(id); };
  virtual void onWheelRotate(uint16_t id, float speed) { parent->onWheelRotate(id, speed); };
};
