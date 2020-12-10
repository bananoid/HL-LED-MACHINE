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
      esp_err_t res = esp_now_send(broadcastAddr, (uint8_t *)&data, sizeof(RequestIdAction));

      if (res == ESP_OK)
      {
        Serial.print("RequestIdAction :: ");
        Serial.println(data.action);
      }
      else if (res == ESP_ERR_ESPNOW_NOT_INIT)
      {
        Serial.print("ESP_ERR_ESPNOW_NOT_INIT");
        Serial.println(data.action);
      }
      else if (res == ESP_ERR_ESPNOW_ARG)
      {
        Serial.print("ESP_ERR_ESPNOW_ARG");
        Serial.println(data.action);
      }
      else if (res == ESP_ERR_ESPNOW_INTERNAL)
      {
        Serial.print("ESP_ERR_ESPNOW_INTERNAL");
        Serial.println(data.action);
      }
      else if (res == ESP_ERR_ESPNOW_NO_MEM)
      {
        Serial.print("ESP_ERR_ESPNOW_NO_MEM");
        Serial.println(data.action);
      }
      else if (res == ESP_ERR_ESPNOW_NOT_FOUND)
      {
        Serial.print("ESP_ERR_ESPNOW_NOT_FOUND");
        Serial.println(data.action);
      }
      else if (res == ESP_ERR_ESPNOW_IF)
      {
        Serial.print("ESP_ERR_ESPNOW_IF");
        Serial.println(data.action);
      }
    }
  }

  void Client::update()
  {
  }

  Client *ClientSingleton = new Client();

} // namespace ESPSortedBroadcast