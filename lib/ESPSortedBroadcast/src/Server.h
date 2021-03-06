#ifndef HL_LIB_ESPSORTEDBROADCASTER_SRC_SERVER
#define HL_LIB_ESPSORTEDBROADCASTER_SRC_SERVER

#include "Peer.h"
#include "Actions.h"

namespace ESPSortedBroadcast
{
  class Server : public Peer
  {
  private:
  public:
    int clientsIdCounter = 0;
    uint8_t idsMap[256][6];

    Server();

    int getIdForAddress(const uint8_t *macaddr);

    void register_recv_cb() override;

    void recv_cb(const uint8_t *macaddr, const uint8_t *incomingData, int len);

    void broadcastCurrentId(const uint8_t *macaddr);
    void broadcastCurrentPosition();
  };

  extern Server *ServerSingleton;

} // namespace ESPSortedBroadcast

#endif /* HL_LIB_ESPSORTEDBROADCASTER_SRC_SERVER */
