#ifndef HL_LIB_ESPSORTEDBROADCASTER_SRC_PEER
#define HL_LIB_ESPSORTEDBROADCASTER_SRC_PEER

#include <Arduino.h>
#include <esp_now.h>
#include "Actions.h"

namespace ESPSortedBroadcast
{
  const uint8_t broadcastAddr[] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

  class Peer
  {
  private:
  public:
    Action currentAction = NO_ACTION;

    Peer();
    ~Peer();

    virtual void begin();
    virtual void update();
    virtual void register_recv_cb();

    static void printMacAddr(const uint8_t *macaddr);
    static Action getActionFromData(const uint8_t *data);
  };

} // namespace ESPSortedBroadcast

#endif /* HL_LIB_ESPSORTEDBROADCASTER_SRC_PEER */
