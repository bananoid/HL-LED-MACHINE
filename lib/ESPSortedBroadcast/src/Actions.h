#ifndef HL_LIB_ESPSORTEDBROADCASTER_SRC_ACTIONS
#define HL_LIB_ESPSORTEDBROADCASTER_SRC_ACTIONS
namespace ESPSortedBroadcast
{

  enum Action
  {
    NO_ACTION,
    SEND_PARAMS,
    REQUEST_ID,
    SEND_ID,
    SYNC
    // BENCHMARK
  };

  typedef struct SendParamsAction
  {
    Action action = SEND_PARAMS;
    float speed = 1;
  } SendParamsAction;

  typedef struct RequestIdAction
  {
    Action action = REQUEST_ID;
  } RequestIdAction;

  typedef struct SendIdAction
  {
    Action action = SEND_ID;
    int id = 0;
  } SendIdAction;

  typedef struct SyncAction
  {
    Action action = SYNC;
    unsigned long position = 0;
  } SyncAction;

} // namespace ESPSortedBroadcast
#endif /* HL_LIB_ESPSORTEDBROADCASTER_SRC_ACTIONS */
