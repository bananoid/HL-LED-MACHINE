#ifndef HL_LIB_ESPSORTEDBROADCASTER_SRC_ACTIONS
#define HL_LIB_ESPSORTEDBROADCASTER_SRC_ACTIONS

#define SERVER_BASE_ACTION_TYPES NO_ACTION, REQUEST_ID, SEND_ID, SYNC

namespace ESPSortedBroadcast
{
  enum BaseActionTypes
  {
    SERVER_BASE_ACTION_TYPES
  };

  struct Action
  {
    uint8_t type = NO_ACTION;
  };

  struct RequestIdAction : public Action
  {
    RequestIdAction()
    {
      type = REQUEST_ID;
    }
  };

  struct SendIdAction : public Action
  {
    SendIdAction()
    {
      type = SEND_ID;
    }
    int id = 0;
  };

  struct SyncAction : public Action
  {
    SyncAction()
    {
      type = SYNC;
    }
    unsigned long position = 0;
  };

} // namespace ESPSortedBroadcast
#endif /* HL_LIB_ESPSORTEDBROADCASTER_SRC_ACTIONS */
