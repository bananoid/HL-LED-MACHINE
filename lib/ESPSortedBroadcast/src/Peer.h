#pragma once

#include <Arduino.h>
#include <esp_now.h>
#include "Actions.h"

#ifndef PEER_TYPES
#define PEER_TYPES DEFAULT_PEER
#endif

#include <BaseMessages.h>

using namespace Messages;

namespace ESPSortedBroadcast
{
  const uint8_t broadcastAddr[] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
  // const uint8_t broadcastAddr[] = {0x24, 0x0A, 0xC4, 0xED, 0x92, 0x0C};

  enum PeerType
  {
    PEER_TYPES
  };

  struct PeerRecord
  {
    String macAddress;
    String typeName;
    PeerType type;
  };

  struct PeerDescription
  {
    int id;
    String macAddress;
    PeerType type;
    String typeName;
    String name;
  };

  class Peer
  {
  private:
  public:
    int currentAction = NO_ACTION;

    Peer();
    ~Peer();

    int channel;

    virtual void begin(int channel, PeerRecord *peerList, int nPeers);
    virtual void registerReceiveDataCB();
    void receiveDataCB(const uint8_t *mac, const uint8_t *incomingData, int len);
    virtual void receiveFilteredDataCB(uint8_t type,
                                       uint8_t sourceId,
                                       uint8_t targetId,
                                       const uint8_t *mac,
                                       const uint8_t *incomingData,
                                       int len);

    int nPeers;
    PeerRecord *peerList;
    PeerDescription peerDescription;
    PeerDescription getDescription();

    // void addPeerRecord(PeerRecord peerRecord);
    void setPeerList(PeerRecord *peerList);

    static void printMacAddr(const uint8_t *macaddr);
    static uint8_t getMessageTypeFromData(const uint8_t *data);

    void broadcastData(const uint8_t *data, size_t len);
    void broadcastMessage(BaseMessage *msg, size_t len);

    void sendDataToAddress(uint8_t *macaddr, const uint8_t *data, size_t len);

    bool enableFilter = true;
  };
}