#include "Server.h"

namespace ESPSortedBroadcast
{
  // Server::Server()
  // {
  // }

  void Server::registerReceiveDataCB()
  {
    Serial.println("Register Server receive callback");
    esp_now_register_recv_cb([](const uint8_t *macaddr, const uint8_t *incomingData, int len) {
      ServerSingleton->recv_cb(macaddr, incomingData, len);
    });
  }

  void Server::recv_cb(const uint8_t *macaddr, const uint8_t *incomingData, int len)
  {
    uint8_t actionType = Server::getMessageTypeFromData(incomingData);

    Serial.print("Receive Action :: ");
    Serial.println(actionType);

    if (actionType == REQUEST_ID)
    {
      broadcastCurrentId(macaddr);
    }
  };

  int Server::getIdForAddress(const uint8_t *macaddr)
  {
    for (int i = 1; i < 256; i++)
    {
      if (
          macaddr[0] == idsMap[i][0] &&
          macaddr[1] == idsMap[i][1] &&
          macaddr[2] == idsMap[i][2] &&
          macaddr[3] == idsMap[i][3] &&
          macaddr[4] == idsMap[i][4] &&
          macaddr[5] == idsMap[i][5])
      {
        return i;
      }
    }
    clientsIdCounter++;
    idsMap[clientsIdCounter][0] = macaddr[0];
    idsMap[clientsIdCounter][1] = macaddr[1];
    idsMap[clientsIdCounter][2] = macaddr[2];
    idsMap[clientsIdCounter][3] = macaddr[3];
    idsMap[clientsIdCounter][4] = macaddr[4];
    idsMap[clientsIdCounter][5] = macaddr[5];
    return clientsIdCounter;
  }

  void Server::broadcastCurrentId(const uint8_t *macaddr)
  {
    int peerId = getIdForAddress(macaddr);

    SendIdAction data;
    data.id = peerId;

    broadcastData((uint8_t *)&data, sizeof(data));

    broadcastCurrentPosition();

    Serial.print("Broadcast id :: ");
    Serial.print(peerId);
    Serial.print(" to client :: ");
    printMacAddr(macaddr);
  }

  void Server::broadcastCurrentPosition()
  {
    SyncAction data;
    data.position = millis();

    Serial.print("Action type :: ");
    Serial.print(data.type);
    Serial.print(" - Send Sync at :: ");
    Serial.println(data.position);

    broadcastData((uint8_t *)&data, sizeof(data));
  }

  Server *ServerSingleton = new Server();
} // namespace ESPSortedBroadcast