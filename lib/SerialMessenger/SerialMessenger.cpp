#include "SerialMessenger.h"

namespace HLSerialMessanger
{
  SerialMessenger::SerialMessenger()
  {
  }

  void SerialMessenger::begin(Stream *stream, int boudrate)
  {
    packetSerial.begin(boudrate);
    packetSerial.setStream(stream);
    packetSerial.setPacketHandler([](const uint8_t *buffer, size_t size) {
      SerialMessengerSingleton->delegate->serialMessengerReceiveData(buffer, size);
    });
    stream->flush();
  }

  void SerialMessenger::sendMessage(BaseMessage *message, int size)
  {
    uint8_t packet[size];
    memcpy(packet, message, size);
    packetSerial.send(packet, size);
  }

  void SerialMessenger::sendData(const uint8_t *data, int len)
  {
    packetSerial.send(data, len);
  }

  void SerialMessenger::update()
  {
    packetSerial.update();
  }

  SerialMessenger *SerialMessengerSingleton = new SerialMessenger();

  uint8_t SerialMessenger::getMessageTypeFromData(const uint8_t *data)
  {
    uint8_t type;
    memcpy(&type, data, sizeof(uint8_t));
    return type;
  }
} // namespace HLSerialMessanger
