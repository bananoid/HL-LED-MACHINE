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
    virtual void serialMessengerReceiveData(const uint8_t *incomingData, int len);
  };

  class SerialMessenger
  {
  private:
  public:
    PacketSerial_<SLIP, 231, PACKET_SIZE> packetSerial;
    SerialMessenger();
    SerialMessengerDelegate *delegate;
    void sendMessage(BaseMessage *message, int size);
    void begin(Stream *stream, int boudrate);
    void update();

    void onReceive(const uint8_t *buffer, size_t size);

    void sendData(const uint8_t *data, int len);
    uint8_t getMessageTypeFromData(const uint8_t *data);

    Stream *stream;
  };

  extern SerialMessenger *SerialMessengerSingleton;

} // namespace HLSerialMessanger
