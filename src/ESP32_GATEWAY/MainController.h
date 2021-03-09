#pragma once

#include <SerialMessenger.h>

using namespace HLSerialMessanger;

class MainController : SerialMessengerDelegate
{
private:
public:
  MainController();
  void begin();
  void update();
  void serialMessengerReceiveMsg(Message *message) override;

  unsigned long lastTime;
};
