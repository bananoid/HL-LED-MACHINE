#include "Peer.h"

#include <WiFi.h>

namespace ESPSortedBroadcast
{

  void Peer::printMacAddr(const uint8_t *macaddr)
  {
    Serial.print(macaddr[0]);
    Serial.print("::");
    Serial.print(macaddr[1]);
    Serial.print("::");
    Serial.print(macaddr[2]);
    Serial.print("::");
    Serial.print(macaddr[3]);
    Serial.print("::");
    Serial.print(macaddr[4]);
    Serial.print("::");
    Serial.print(macaddr[5]);
    Serial.println();
  }

  Action Peer::getActionFromData(const uint8_t *data)
  {
    Action action;
    memcpy(&action, data, sizeof(action));
    return action;
  }

  Peer::Peer()
  {
  }

  Peer::~Peer()
  {
  }

  void Peer::begin()
  {
    WiFi.mode(WIFI_STA);
    // Serial.println(WiFi.macAddress());
    // WiFi.disconnect();

    if (esp_now_init() != ESP_OK)
    {
      Serial.println("Error initializing ESP-NOW");
      return;
    }

    register_recv_cb();

    // register broadcast address
    esp_now_peer_info_t peerInfo;
    peerInfo.channel = 3;
    peerInfo.encrypt = false;

    memcpy(peerInfo.peer_addr, broadcastAddr, 6);
    esp_err_t epsAddPeerRes = esp_now_add_peer(&peerInfo);
    if (epsAddPeerRes != ESP_OK)
    {
      Serial.println("Failed to add peer");

      if (epsAddPeerRes == ESP_ERR_ESPNOW_NOT_INIT)
      {
        Serial.println("ESP_ERR_ESPNOW_NOT_INIT");
      }
      if (epsAddPeerRes == ESP_ERR_ESPNOW_ARG)
      {
        Serial.println("ESP_ERR_ESPNOW_ARG");
      }
      if (epsAddPeerRes == ESP_ERR_ESPNOW_FULL)
      {
        Serial.println("ESP_ERR_ESPNOW_FULL");
      }
      if (epsAddPeerRes == ESP_ERR_ESPNOW_NO_MEM)
      {
        Serial.println("ESP_ERR_ESPNOW_NO_MEM");
      }
      if (epsAddPeerRes == ESP_ERR_ESPNOW_EXIST)
      {
        Serial.println("ESP_ERR_ESPNOW_EXIST");
      }
      return;
    }
  }

  void Peer::update()
  {
  }

  void Peer::register_recv_cb()
  {
  }
} // namespace ESPSortedBroadcast