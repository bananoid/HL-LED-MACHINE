#include <Arduino.h>

// #define IS_SERVER // Comment for client mode

#include <ESPSortedBroadcast.h>

#ifdef IS_SERVER

void setup()
{
  Serial.begin(115200);

  ESPSortedBroadcast::ServerSingleton->begin();
}

void loop()
{
  ESPSortedBroadcast::ServerSingleton->update();
}

#else

void setup()
{
  Serial.begin(115200);

  ESPSortedBroadcast::ClientSingleton->begin();
}

void loop()
{
  ESPSortedBroadcast::ClientSingleton->update();
}

#endif