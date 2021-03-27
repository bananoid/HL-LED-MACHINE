#include "SerialMessenger.h"

namespace HLSerialMessanger
{
  SerialMessenger::SerialMessenger()
  {
  }

  void SerialMessenger::begin(Stream *stream, int boudrate)
  {
    this->stream = stream;
    packetSerial.begin(boudrate);
    packetSerial.setStream(stream);
    packetSerial.setPacketHandler([](const uint8_t *buffer, size_t size) {
      BaseMessage message;
      memcpy(&message, buffer, size);
      SerialMessengerSingleton->delegate->serialMessengerReceiveMsg(&message);
      SerialMessengerSingleton->delegate->serialMessengerReceiveData(buffer, size);
    });
  }

  void SerialMessenger::sendMessage(BaseMessage *message)
  {
    int size = sizeof(&message);
    uint8_t packet[size];
    memcpy(packet, message, size);
    packetSerial.send(packet, size);
  }

  void SerialMessenger::sendData(const uint8_t *data, int len)
  {
    stream->flush();
    packetSerial.send(data, len);
  }

  void SerialMessenger::update()
  {
    packetSerial.update();
  }

  SerialMessenger *SerialMessengerSingleton = new SerialMessenger();

} // namespace HLSerialMessanger
