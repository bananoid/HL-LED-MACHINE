#include "Server.h"

namespace ESPSortedBroadcast
{
  void Server::register_recv_cb()
  {
    esp_now_register_recv_cb([](const uint8_t *macaddr, const uint8_t *incomingData, int len) {
      ServerSingleton->recv_cb(macaddr, incomingData, len);
    });
  }

  void Server::recv_cb(const uint8_t *macaddr, const uint8_t *incomingData, int len)
  {
    ESPSortedBroadcast::Action action = Server::getActionFromData(incomingData);

    Serial.print("Receive Action :: ");
    Serial.println(action);

    currentAction = action;
    if (currentAction == REQUEST_ID)
    {
      broadCastCurrentId(macaddr);
    }
  };

  void Server::broadCastCurrentId(const uint8_t *macaddr)
  {
    Serial.print("Broadcast id for :: ");
    Serial.print(clientsIdCounter);
    Serial.print(" to client :: ");
    printMacAddr(macaddr);

    SendIdAction data;
    data.id = clientsIdCounter;
    esp_now_send(broadcastAddr, (uint8_t *)&data, sizeof(SendIdAction));

    clientsIdCounter++;
  }

  void Server::broadCastCurrentPosition()
  {
    SyncAction data;
    data.position = millis();

    Serial.print("Send Sync at :: ");
    Serial.println(data.position);
    esp_now_send(broadcastAddr, (uint8_t *)&data, sizeof(SyncAction));
  }

  void Server::update()
  {
    // if (currentAction == SEND_PARAMS)
    // {
    SendParamsAction data;
    data.speed = sinf(millis() / 1000.0) * 10000;
    esp_now_send(broadcastAddr, (uint8_t *)&data, sizeof(SendParamsAction));
    // delay(16);
    // }
  }

  Server *ServerSingleton = new Server();
} // namespace ESPSortedBroadcast