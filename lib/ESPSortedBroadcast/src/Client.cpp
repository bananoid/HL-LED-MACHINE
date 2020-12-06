#include "Client.h"

namespace ESPSortedBroadcast
{
  void Client::register_recv_cb()
  {
    esp_now_register_recv_cb([](const uint8_t *macaddr, const uint8_t *incomingData, int len) {
      ClientSingleton->recv_cb(macaddr, incomingData, len);
    });
  }

  void Client::recv_cb(const uint8_t *macaddr, const uint8_t *incomingData, int len)
  {
    Action action = getActionFromData(incomingData);

    // Serial.print("Acction received :: ");
    // Serial.print(action);
    // Serial.print(" \t from :: ");
    // printMacAddr(macaddr);

    if (action == SEND_ID && clientId == 0)
    {
      SendIdAction data;
      memcpy(&data, incomingData, sizeof(data));
      clientId = data.id;

      Serial.print("clientId assigned :: ");
      Serial.println(clientId);

      currentAction = NO_ACTION;
      return;
    }

    if (action == SYNC)
    {
      SyncAction data;
      memcpy(&data, incomingData, sizeof(data));
      Serial.print("Sync to :: ");
      Serial.println(data.position);
    }
  }

  void Client::update()
  {
    if (clientId == 0)
    {
      RequestIdAction data;
      esp_now_send(broadcastAddr, (uint8_t *)&data, sizeof(SendParamsAction));
    }
  }

  Client *ClientSingleton = new Client();

} // namespace ESPSortedBroadcast