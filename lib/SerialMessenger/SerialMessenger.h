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
    virtual void serialMessengerReceiveMsg(AudioSignalsMsg *message);
  };

  class SerialMessenger
  {
  private:
  public:
    PacketSerial_<COBS, 0, PACKET_SIZE> packetSerial;
    SerialMessenger(Stream *stream);
    void sendMessage(Message *message);
    void update();

    void onReceive(const uint8_t *buffer, size_t size);
  };
} // namespace HLSerialMessanger
