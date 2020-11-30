#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>

#define IS_SERVER // Comment for client mode

#define CHANNEL 3

uint8_t broadcastAddr[] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff}; // ALL RECEIVERS

typedef struct PayloadStruct
{
  unsigned long timestamp_ms;
  unsigned long counter;
} PayloadStruct;

PayloadStruct payloadData;

#ifdef IS_SERVER

unsigned long counter = 0;

// void recv_cb(const uint8_t *macaddr, const uint8_t *incomingData, int len)
// {

//   if (!esp_now_is_peer_exist(macaddr))
//   {

//     esp_now_peer_info_t peerInfo;
//     peerInfo.channel = CHANNEL;
//     peerInfo.encrypt = false;

//     memcpy(peerInfo.peer_addr, macaddr, 6);

//     if (esp_now_add_peer(&peerInfo) != ESP_OK)
//     {
//       Serial.println("Failed to add peer");
//       return;
//     }
//     else
//     {
//       String s = String((char *)macaddr);
//       Serial.print("Peer added with mac :: ");
//       Serial.println(s);
//     }
//   }
// };

void setup()
{
  Serial.begin(9600);

  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK)
  {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // esp_now_register_recv_cb(recv_cb);

  // register peer
  esp_now_peer_info_t peerInfo;
  peerInfo.channel = CHANNEL;
  peerInfo.encrypt = false;

  // register all peer
  memcpy(peerInfo.peer_addr, broadcastAddr, 6);
  if (esp_now_add_peer(&peerInfo) != ESP_OK)
  {
    Serial.println("Failed to add peer");
    return;
  }
}

void loop()
{

  // Serial.println(WiFi.macAddress());

  counter++;
  payloadData.counter = counter;
  payloadData.timestamp_ms = millis();
  esp_now_send(broadcastAddr, (uint8_t *)&payloadData, sizeof(PayloadStruct));
  // esp_now_send(0, (uint8_t *)&payloadData, sizeof(PayloadStruct));
}

#else

void recv_cb(const uint8_t *macaddr, const uint8_t *incomingData, int len)
{
  memcpy(&payloadData, incomingData, sizeof(payloadData));
  Serial.print("Bytes received: ");
  Serial.println(len);
  Serial.println("data: ");
  Serial.println(payloadData.counter);
  Serial.println(payloadData.timestamp_ms);
  Serial.println("-------------");
}

void setup()
{
  Serial.begin(9600);

  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK)
  {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_register_recv_cb(recv_cb);
}

void loop()
{
}

#endif