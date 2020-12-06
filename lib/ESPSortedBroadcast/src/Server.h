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
    int clientsIdCounter;
    Action currentAction;

    void register_recv_cb() override;
    void update() override;

    void recv_cb(const uint8_t *macaddr, const uint8_t *incomingData, int len);

    void broadCastCurrentId(const uint8_t *macaddr);
    void broadCastCurrentPosition();
  };

  extern Server *ServerSingleton;

} // namespace ESPSortedBroadcast

#endif /* HL_LIB_ESPSORTEDBROADCASTER_SRC_SERVER */
