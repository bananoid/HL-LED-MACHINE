#pragma once
#include <Arduino.h>

#include "UIGFXContext.h"
#include <GFXUtils.h>
using namespace GFX;

#include <vector>
using namespace std;

class UIView
{
private:
public:
  uint16_t focusIndex = 0;
  uint16_t depht = 0;

  Point scroll = {0, 0};

  UIGFXContext *ctx = nullptr;
  Rect frame = {0, 0, 16, 16};
  String label = "View";
  vector<UIView *> childs;
  UIView *parent;
  bool loopFocusSelection = false;
  UIView(){};
  virtual void show();
  virtual void build(){};
  virtual void layout();
  void layoutChilds();
  virtual void update(){};
  virtual void draw(){};
  UIView *addChild(UIView *view);

  bool isFocused();
  // virtual void onKeyPress(uint16_t id) { parent->onKeyPress(id); };
  // virtual void onKeyRelease(uint16_t id) { parent->onKeyRelease(id); };
  // virtual void onWheelRotate(uint16_t id, float speed) { parent->onWheelRotate(id, speed); };

  virtual void setFocusIndex(int16_t inx);
  virtual void focusPrev();
  virtual void focusNext();
  virtual void focusIn();
  virtual void focusOut();
};
