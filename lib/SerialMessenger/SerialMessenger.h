#pragma once

#include <PacketSerial.h>

#include <BaseMessages.h>

#define PACKET_SIZE 256

using namespace Messages;

namespace HLSerialMessanger
{
  class SerialMessengerDelegate
  {
  public:
    virtual void serialMessengerReceiveMsg(Message *message);
  };

  class SerialMessenger
  {
  private:
  public:
    PacketSerial_<COBS, 0, PACKET_SIZE> packetSerial;
    SerialMessenger();
    SerialMessengerDelegate *delegate;
    void sendMessage(Message *message);
    void begin(Stream *stream, int boudrate);
    void update();

    void onReceive(const uint8_t *buffer, size_t size);
  };

  extern SerialMessenger *SerialMessengerSingleton;

} // namespace HLSerialMessanger
