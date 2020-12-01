#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>

// #define IS_SERVER // Comment for client mode

#define CHANNEL 3

uint8_t broadcastAddr[] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff}; // ALL RECEIVERS

//Server mac :: 16::82::28::102::150::204

enum Action
{
  NO_ACTION,
  SEND_PARAMS,
  REQUEST_ID,
  SEND_ID,
  SYNC
  // BENCHMARK
};

Action currentAction = NO_ACTION;

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

// typedef struct BenchmarkAction
// {
//   Action action = BENCHMARK;
//   unsigned long timestamp;
//   unsigned long transactionCounter;
// } BenchmarkAction;

void printMacAddr(const uint8_t *macaddr)
{
  Serial.print(macaddr[0]);
  Serial.print("::");
  Serial.print(macaddr[1]);
  Serial.print("::");
  Serial.print(macaddr[2]);
  Serial.print("::");
  Serial.print(macaddr[3]);
  Serial.print("::");
  Serial.print(macaddr[4]);
  Serial.print("::");
  Serial.print(macaddr[5]);
  Serial.println();
}

Action getActionFromData(const uint8_t *data)
{
  Action action;
  memcpy(&action, data, sizeof(action));
  return action;
}

#ifdef IS_SERVER

unsigned long transactionCounter = 0;

#define MAX_NUM_CLIENT 255
const uint8_t *clientsList[MAX_NUM_CLIENT];

int clientsIdCounter = 1;

void broadCastCurrentId(const uint8_t *macaddr)
{
  Serial.print("Broadcast id for :: ");
  Serial.print(clientsIdCounter);
  Serial.print(" to client :: ");
  printMacAddr(macaddr);

  SendIdAction data;
  data.id = clientsIdCounter;
  esp_now_send(broadcastAddr, (uint8_t *)&data, sizeof(SendIdAction));

  clientsIdCounter++;
}

void recv_cb(const uint8_t *macaddr, const uint8_t *incomingData, int len)
{
  Action action = getActionFromData(incomingData);

  Serial.print("Receive Action :: ");
  Serial.println(action);

  currentAction = action;
  if (currentAction == REQUEST_ID)
  {
    broadCastCurrentId(macaddr);
  }
};

void send_cb(const uint8_t *mac_addr, esp_now_send_status_t status)
{
  if (
      mac_addr[0] == 255 &&
      mac_addr[1] == 255 &&
      mac_addr[2] == 255 &&
      mac_addr[3] == 255 &&
      mac_addr[4] == 255 &&
      mac_addr[5] == 255)
  {
    return;
  }

  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.print(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
  printMacAddr(mac_addr);
}

void setup()
{
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  Serial.println(WiFi.macAddress());
  WiFi.disconnect();

  if (esp_now_init() != ESP_OK)
  {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_register_recv_cb(recv_cb);

  // register broadcast address
  esp_now_peer_info_t peerInfo;
  peerInfo.channel = CHANNEL;
  peerInfo.encrypt = false;

  memcpy(peerInfo.peer_addr, broadcastAddr, 6);
  if (esp_now_add_peer(&peerInfo) != ESP_OK)
  {
    Serial.println("Failed to add peer");
    return;
  }
}

void loop()
{
  // transactionCounter++;

  if (currentAction == SEND_PARAMS)
  {
    SendParamsAction data;
    data.speed = sinf(millis() / 1000.0) * 10000;
    esp_now_send(broadcastAddr, (uint8_t *)&data, sizeof(SendParamsAction));
    delay(16);
  }
}

#else

SendParamsAction paramsData;

const uint8_t *serverAddr = nullptr;
int clientId = 0;
bool serverAdded = false;

void recv_cb(const uint8_t *macaddr, const uint8_t *incomingData, int len)
{
  Action action = getActionFromData(incomingData);
  Serial.print("Acction received :: ");
  Serial.print(action);
  Serial.print(" \t from :: ");
  printMacAddr(macaddr);

  if (action == SEND_ID && clientId == 0)
  {
    SendIdAction data;
    memcpy(&data, incomingData, sizeof(data));
    clientId = data.id;

    Serial.print("clientId assigned :: ");
    Serial.println(clientId);

    currentAction = NO_ACTION;

    return;
  }
}

void setup()
{
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  Serial.println(WiFi.macAddress());
  WiFi.disconnect();

  if (esp_now_init() != ESP_OK)
  {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_register_recv_cb(recv_cb);

  // register broadcast address
  esp_now_peer_info_t peerInfo;
  peerInfo.channel = CHANNEL;
  peerInfo.encrypt = false;

  memcpy(peerInfo.peer_addr, broadcastAddr, 6);
  if (esp_now_add_peer(&peerInfo) != ESP_OK)
  {
    Serial.println("Failed to add peer");
    return;
  }

  currentAction = REQUEST_ID;
}

void loop()
{
  if (currentAction == REQUEST_ID)
  {
    RequestIdAction data;
    esp_now_send(broadcastAddr, (uint8_t *)&data, sizeof(SendParamsAction));
    delay(200);
  }
  else
  {
    Serial.print("RUN With id :: ");
    Serial.println(clientId);
    delay(500);
  }
}

#endif