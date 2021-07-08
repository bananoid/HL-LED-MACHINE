#pragma once

#include "config.h"
#include <TaskSchedulerDeclarations.h>

#include "UIGFXContext.h"
#include "UIView.h"

#include <Encoder.h>
#include <Bounce2.h>

#include <map>
#include <memory>

#include <GFXUtils.h>
using namespace GFX;

#include <vector>
using namespace std;

struct EncoderConfig
{
  uint8_t a;
  uint8_t b;
};

struct ButtonConfig
{
  uint8_t pin;
  uint8_t portType;
  bool invert;
};

class EncoderWrapper
{
public:
  int32_t value = 0;
  int32_t lastValue = 0;
  int32_t speed = 0;

  Encoder *encoder;
  EncoderWrapper(uint8_t pin1, uint8_t pin2)
  {
    encoder = new Encoder(pin1, pin2);
  }
  void update()
  {
    value = encoder->read() / 4;
    speed = (value - lastValue);
    lastValue = value;
  }
};

typedef std::map<uint16_t, ButtonConfig> MapIdToButtonConfig;
typedef std::map<uint16_t, EncoderConfig> MapIdToEncoderConfig;

class UIGFXContext;
class UIView;
class UIViewController
{
public:
  Rect screenBounds = {0, 0, 128, 128};
  UIGFXContext *ctx;
  Task updateTask;
  UIView *rootView;
  UIView *focusView;
  vector<UIView *> viewStack;
  virtual UIView *initRootView();
  virtual void init(Scheduler *runner);
  void pushView(UIView *view);
  void popView();

  std::map<uint16_t, Bounce2::Button *> buttonKeys;
  std::map<uint16_t, EncoderWrapper *> wheelEncoders;

  void initKeys(MapIdToButtonConfig map);
  void initWheels(MapIdToEncoderConfig map);
  // void initLeds(MapPinToId map);

  UIViewController();
  virtual void update();
  void draw();

  void dispatchKeyPress(uint16_t id);
  void dispatchKeyRelease(uint16_t id);
  void dispatchWheelRotate(uint16_t id, float speed);
};