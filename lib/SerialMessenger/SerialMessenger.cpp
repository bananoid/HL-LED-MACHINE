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
      Message message;
      memcpy(&message, buffer, size);
      SerialMessengerSingleton->delegate->serialMessengerReceiveMsg(&message);
    });
  }

  void SerialMessenger::sendMessage(Message *message)
  {
    int size = sizeof(&message);
    uint8_t packet[size];
    memcpy(packet, message, size);
    packetSerial.send(packet, size);
  }

  void SerialMessenger::update()
  {
    packetSerial.update();
  }

  SerialMessenger *SerialMessengerSingleton = new SerialMessenger();

} // namespace HLSerialMessanger
