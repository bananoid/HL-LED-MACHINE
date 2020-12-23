#pragma once
#include "SerialMessenger.h"
namespace HLSerialMessanger
{
  SerialMessenger::SerialMessenger(Stream *stream)
  {
    packetSerial.begin(80000000);
    packetSerial.setStream(stream);
    packetSerial.setPacketHandler([](const uint8_t *buffer, size_t size) {
      
    });
  }

  void SerialMessenger::sendMessage(Message *message)
  {
    const uint8_t *packet;

    memcpy(&packet, message, sizeof(&message));
    packetSerial.send(packet, sizeof(&message));
  }

  void SerialMessenger::update()
  {
    packetSerial.update();
  }

} // namespace HLSerialMessanger
