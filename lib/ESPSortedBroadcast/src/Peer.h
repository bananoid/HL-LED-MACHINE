#ifndef HL_LIB_ESPSORTEDBROADCASTER_SRC_PEER
#define HL_LIB_ESPSORTEDBROADCASTER_SRC_PEER

#include <Arduino.h>
#include <esp_now.h>
#include "Actions.h"
#include "Boards.h"

namespace ESPSortedBroadcast
{
  const uint8_t broadcastAddr[] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
  // const uint8_t broadcastAddr[] = {0x24, 0x0A, 0xC4, 0xED, 0x92, 0x0C};

  class Peer
  {
  private:
  public:
    int currentAction = NO_ACTION;

    Peer();
    ~Peer();

    int channel;

    virtual void begin(int channel = 0);
    virtual void registerReceiveDataCB();
    virtual void receiveDataCB(const uint8_t *mac, const uint8_t *incomingData, int len);

    board *boardList;
    board_info boardInfo;
    // void getOwnBoardInformation();

    static void printMacAddr(const uint8_t *macaddr);
    static uint8_t getMessageTypeFromData(const uint8_t *data);

    void broadcastData(const uint8_t *data, size_t len);

    void sendDataToAddress(uint8_t *macaddr, const uint8_t *data, size_t len);
  };

} // namespace ESPSortedBroadcast

#endif /* HL_LIB_ESPSORTEDBROADCASTER_SRC_PEER */
