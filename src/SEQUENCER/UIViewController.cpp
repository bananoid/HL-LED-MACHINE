#include "UIViewController.h"

#include "config.h"

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

void UIViewController::initKeys(MapIdToButtonConfig map)
{
  for (auto const &p : map)
  {
    auto btn = new Bounce2::Button();
    btn->attach(p.second.pin, p.second.portType);
    btn->interval(5);
    btn->setPressedState(p.second.invert ? 0 : 1);
    buttonKeys.insert({p.first, btn});
  }
}
void UIViewController::initWheels(MapIdToEncoderConfig map)
{
  for (auto const &p : map)
  {
    wheelEncoders[p.first] = new EncoderWrapper(p.second.a, p.second.b);
  }
}
// void UIViewController::initLeds(MapPinToId map) {}

void UIViewController::update()
{
  for (auto const &p : buttonKeys)
  {
    p.second->update();

    // if (focusView != nullptr)
    // {
    //   if (p.second->released())
    //   {
    //     focusView->onKeyRelease(p.first);
    //   }
    // }

    if (p.second->pressed())
    {
      Serial.printf("key pressed %i\n", p.first);
    }
  }

  for (auto const &p : wheelEncoders)
  {
    p.second->update();

    if (p.second->speed != 0)
    {
      Serial.println(p.second->speed);
    }
  }
}

void UIViewController::draw()
{
  ctx->clear();
  rootView->show();
  ctx->commit();
}
