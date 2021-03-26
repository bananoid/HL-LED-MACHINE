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
    uint8_t type;
    memcpy(&type, data, sizeof(uint8_t));
    return type;
  }

  Peer::Peer()
  {
  }

  Peer::~Peer()
  {
  }

  void Peer::begin(int channel, PeerRecord *peerList, int nPeers)
  {
    WiFi.mode(WIFI_STA);
    Serial.println(WiFi.macAddress());
    WiFi.disconnect();

    if (esp_now_init() != ESP_OK)
    {
      Serial.println("Error initializing ESP-NOW");
      return;
    }

    this->nPeers = nPeers;
    setPeerList(peerList);
    // boardInfo = getBoardInfo(WiFi.macAddress(), boardList);
    peerDescription = getDescription();

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

  void Peer::setPeerList(PeerRecord *peerList)
  {
    this->peerList = peerList;
  }

  PeerDescription Peer::getDescription()
  {
    // boardInfo = getBoardInfo(WiFi.macAddress(), boardList);
    PeerDescription peerDescription;

    // int nBoards = 5;
    // int nBoards = sizeof(boardList); // TODO
    String macAddress = WiFi.macAddress();

    for (int i = 0; i < nPeers; i++)
    {
      if (macAddress == peerList[i].macAddress)
      {
        peerDescription.id = i + 1;
        peerDescription.macAddress = macAddress;
        peerDescription.type = peerList[i].type;
        peerDescription.typeName = peerList[i].typeName;
        peerDescription.name = "B" + String(peerDescription.id) + " [" + peerDescription.typeName + "]";
        return peerDescription;
      }
    }

    peerDescription.id = 999;
    peerDescription.macAddress = macAddress;
    peerDescription.type = DEFAULT_PEER;
    peerDescription.typeName = "unknown";
    peerDescription.name = "B" + String(peerDescription.id) + " [UNKNWON]";
    return peerDescription;
  }
} // namespace ESPSortedBroadcast