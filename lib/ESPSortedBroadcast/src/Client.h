#ifndef HL_LIB_ESPSORTEDBROADCAST_SRC_CLIENT
#define HL_LIB_ESPSORTEDBROADCAST_SRC_CLIENT

#include "Peer.h"
#include "Actions.h"

namespace ESPSortedBroadcast
{
  class Client : public Peer
  {
  private:
  public:
    SendParamsAction paramsData;
    int clientId = 0;

    // void begin() override;
    void register_recv_cb() override;
    void update() override;

    void recv_cb(const uint8_t *macaddr, const uint8_t *incomingData, int len);
  };

  extern Client *ClientSingleton;

} // namespace ESPSortedBroadcast
#endif /* HL_LIB_ESPSORTEDBROADCAST_SRC_CLIENT */
