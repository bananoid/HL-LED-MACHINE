#pragma once
#include <Peer.h>

#include "Screen.h"
#include "COMMON/Messages.h"
#include "COMMON/Boards.h"

class HLPeer : public ESPSortedBroadcast::Peer
{
public:
    HLPeer();

    Screen *screen;

    board_info boardInfo;

    uint8_t messageTypeSubs[];

    void beginServer();
    void ping();

    void getOwnBoardInformation();

    void displayHeader();

    BaseMessage getRandomMessage();

    static void onDataReceived(const uint8_t *mac, const uint8_t *incomingData, int len);
};

extern HLPeer *HLPeerSingleton;