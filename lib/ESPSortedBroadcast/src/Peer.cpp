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

  uint8_t Peer::getMessageTypeFromData(const uint8_t *data)
  {
    int action;
    memcpy(&action, data, sizeof(action));
    return action;
  }

  Peer::Peer()
  {
  }

  Peer::~Peer()
  {
  }

  void Peer::begin(int channel)
  {
    WiFi.mode(WIFI_STA);
    Serial.println(WiFi.macAddress());
    WiFi.disconnect();

    if (esp_now_init() != ESP_OK)
    {
      Serial.println("Error initializing ESP-NOW");
      return;
    }

    boardInfo = getBoardInfo(WiFi.macAddress(), boardList);

    registerReceiveDataCB();

    esp_now_peer_info_t peerInfo;
    peerInfo.channel = channel;
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

    Serial.println("Broadcast Peer added");
  }

  void Peer::registerReceiveDataCB()
  {
  }

  void Peer::receiveDataCB(const uint8_t *mac, const uint8_t *incomingData, int len)
  {
  }

  void Peer::broadcastData(const uint8_t *data, size_t len)
  {
    esp_now_send(broadcastAddr, data, len);
  }

  void Peer::sendDataToAddress(uint8_t *macaddr, const uint8_t *data, size_t len)
  {
    esp_now_send((uint8_t *)&macaddr, data, len);
  }

  // void Peer::getOwnBoardInformation()
  // {
  //   boardInfo = getBoardInfo(WiFi.macAddress(), boardList);
  // }
} // namespace ESPSortedBroadcast