#include "Client.h"

namespace ESPSortedBroadcast
{
  void Client::registerReceiveDataCB()
  {
    esp_now_register_recv_cb([](const uint8_t *macaddr, const uint8_t *incomingData, int len) {
      ClientSingleton->recv_cb(macaddr, incomingData, len);
    });
  }

  void Client::recv_cb(const uint8_t *macaddr, const uint8_t *incomingData, int len)
  {
    uint8_t action = getMessageTypeFromData(incomingData);

    if (action != SYNC)
    {
      Serial.print("Acction received :: ");
      Serial.print(action);
      Serial.print(" \t from :: ");
      printMacAddr(macaddr);
    }

    if (action == SEND_ID && clientId == 0)
    {

      SendIdAction data;
      memcpy(&data, incomingData, sizeof(data));
      clientId = data.id;

      Serial.print("clientId assigned :: ");
      Serial.println(clientId);

      if (delegate)
      {
        delegate->clientReceveClientIndex(data);
      }
      return;
    }

    if (action == SYNC)
    {
      SyncAction data;
      memcpy(&data, incomingData, sizeof(data));
      if (delegate)
      {
        delegate->clientReceveSyncAction(data);
      }
      return;
    }
  }

  void Client::requestClientIndex()
  {
    if (clientId == 0)
    {
      RequestIdAction data;
      broadcastData((uint8_t *)&data, sizeof(data));
    }
  }

  Client *ClientSingleton = new Client();

} // namespace ESPSortedBroadcast