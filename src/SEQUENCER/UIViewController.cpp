#include "UIViewController.h"

#include "config.h"

UIViewController::UIViewController()
{
}
void UIViewController::init(Scheduler *runner)
{
  ctx = new UIGFXContext();
  ctx->controller = this;
  rootView = initRootView();

  // viewStack.clear();
  pushView(rootView);

  updateTask.set(TASK_MILLISECOND * 16, TASK_FOREVER, [this]()
                 {
                   update();
                   draw();
                 });
  runner->addTask(updateTask);
  updateTask.enable();
}

void UIViewController::pushView(UIView *view)
{
  if (view->ctx == nullptr)
  {
    view->ctx = ctx;
    view->frame = screenBounds;
    view->build();
    view->layout();
  }

  viewStack.push_back(view);

  focusView = view;
}
void UIViewController::popView()
{
  if (viewStack.size() <= 1)
  {
    return;
  }
  viewStack.pop_back();
  viewStack.back()->focusIn();
};

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

    // if (p.second->pressed())
    // {
    //   Serial.printf("key pressed %i\n", p.first);
    // }
  }

  for (auto const &p : wheelEncoders)
  {
    p.second->update();

    // if (p.second->speed != 0)
    // {
    //   Serial.println(p.second->speed);
    // }
  }

  if (focusView == nullptr)
  {
    return;
  }

  auto leftWheelSpeed = wheelEncoders[WHEEL_ID_LEFT]->speed;
  if (!buttonKeys[KEY_ID_WHEEL_LEFT]->isPressed())
  {

    if (leftWheelSpeed > 0)
    {
      focusView->focusNext();
    }
    else if (leftWheelSpeed < 0)
    {
      focusView->focusPrev();
    }
  }
  else
  {
    if (leftWheelSpeed > 0)
    {
      focusView->focusIn();
    }
    else if (leftWheelSpeed < 0)
    {
      focusView->focusOut();
    }
  }
}

void UIViewController::draw()
{
  ctx->clippingBounds = screenBounds;
  ctx->clear();
  viewStack.back()->show();
  ctx->commit();
}
