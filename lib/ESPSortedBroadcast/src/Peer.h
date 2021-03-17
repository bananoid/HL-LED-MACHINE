#ifndef HL_LIB_ESPSORTEDBROADCASTER_SRC_PEER
#define HL_LIB_ESPSORTEDBROADCASTER_SRC_PEER

#include <Arduino.h>
#include <esp_now.h>
#include "Actions.h"

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

    virtual void begin();
    virtual void register_recv_cb();

    static void printMacAddr(const uint8_t *macaddr);
    static uint8_t getActionTypeFromData(const uint8_t *data);

    void broadcastData(const uint8_t *data, size_t len);

    void sendDataToAddress(uint8_t *macaddr, const uint8_t *data, size_t len);
  };

} // namespace ESPSortedBroadcast

#endif /* HL_LIB_ESPSORTEDBROADCASTER_SRC_PEER */
