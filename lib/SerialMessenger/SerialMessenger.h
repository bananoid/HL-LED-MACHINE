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
    virtual void serialMessengerReceiveMsg(BaseMessage *message);
    virtual void serialMessengerReceiveData(const uint8_t *incomingData, int len);
  };

  class SerialMessenger
  {
  private:
  public:
    PacketSerial_<COBS, 0, PACKET_SIZE> packetSerial;
    SerialMessenger();
    SerialMessengerDelegate *delegate;
    void sendMessage(BaseMessage *message);
    void begin(Stream *stream, int boudrate);
    void update();

    void onReceive(const uint8_t *buffer, size_t size);

    void sendData(const uint8_t *data, int len);
  };

  extern SerialMessenger *SerialMessengerSingleton;

} // namespace HLSerialMessanger
