#pragma once

#include "config.h"
#include <TaskSchedulerDeclarations.h>

#include "UIGFXContext.h"
#include "UIView.h"

class UIViewController
{
public:
  UIGFXContext *ctx;
  Task updateTask;
  UIView *rootView;
  virtual UIView *initRootView();
  virtual void init(Scheduler *runner);

  UIViewController();
  virtual void update();
  void draw();
};