#include <Arduino.h>

// #define IS_SERVER // Comment for client mode

#include <ESPSortedBroadcast.h>
// #include <Server.h>

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

// #include <FastLED.h>

#include <FastLEDRenderer.h>
#include <GFXUtils.h>
#include <Client.h>

LEDStrips::FastLEDRenderer ledRenderer;

#define LS_NUM_LEDS_PER_STRIP 16
#define LS_NUM_STRIPS 1
#define LS_DATA_PIN 2

void setup()
{
  Serial.begin(115200);

  ESPSortedBroadcast::ClientSingleton->begin();

  ledRenderer.begin();
}

void loop()
{
  ESPSortedBroadcast::ClientSingleton->update();

  int clientInx = ESPSortedBroadcast::ClientSingleton->clientId;

  for (size_t i = 0; i < LS_NUM_LEDS_PER_STRIP; i++)
  {
    GFXUtils::fRGB color;
    if (i + 1 <= clientInx)
    {
      color = GFXUtils::fRGB(0, 0, 1);
    }
    else
    {
      color = GFXUtils::fRGB(1, 0, 0);
    }
    ledRenderer.setPixel(i, color);
  }
  ledRenderer.show();
}

#endif