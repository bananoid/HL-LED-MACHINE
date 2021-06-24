#include "UIViewController.h"

UIViewController::UIViewController()
{
}
void UIViewController::init(Scheduler *runner)
{
  ctx = new UIGFXContext();
  rootView = initRootView();
  rootView->ctx = ctx;
  rootView->frame.w = 128;
  rootView->frame.h = 128;
  rootView->build();

  updateTask.set(TASK_MILLISECOND * 16, TASK_FOREVER, [this]()
                 {
                   update();
                   draw();
                 });
  runner->addTask(updateTask);
  updateTask.enable();
}
UIView *UIViewController::initRootView()
{
  return new UIView();
}

void UIViewController::update()
{
}

void UIViewController::draw()
{
  ctx->clear();
  rootView->show();
  ctx->commit();
}