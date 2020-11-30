#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>

#define IS_SERVER // Comment for client mode

#define CHANNEL 3

uint8_t broadcastAddr[] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff}; // ALL RECEIVERS

enum Action
{
  ASSIGN_ID,
  SEND_PARAMS
};

typedef struct SendParamsAction
{
  Action action = SEND_PARAMS;
  unsigned long timestamp;
  unsigned long transactionCounter;
} SendParamsAction;

typedef struct AssignIdAction
{
  Action action = ASSIGN_ID;
  int id = 0;
} AssignIdAction;

Action getActionFromData(const uint8_t *data)
{
  Action action;
  memcpy(&action, data, sizeof(action));
  return action;
}

// #ifdef IS_SERVER

unsigned long transactionCounter = 0;

int clientsIdCounter = 0;

// Client ID start from 1
void sendIdToClient(const uint8_t *macaddr)
{
  clientsIdCounter++;

  AssignIdAction data;
  data.id = clientsIdCounter;

  esp_now_send(macaddr, (uint8_t *)&data, sizeof(data));
  delay(100);
}

void recv_cb(const uint8_t *macaddr, const uint8_t *incomingData, int len)
{
  Action action = getActionFromData(incomingData);

  Serial.print("Receive Action :: ");
  Serial.println(action);

  if (!esp_now_is_peer_exist(macaddr))
  {

    esp_now_peer_info_t peerInfo;
    peerInfo.channel = CHANNEL;
    peerInfo.encrypt = false;

    memcpy(peerInfo.peer_addr, macaddr, 6);

    if (esp_now_add_peer(&peerInfo) != ESP_OK)
    {
      Serial.println("Failed to add peer");
      return;
    }
    else
    {
      Serial.print("Peer added with mac :: ");
      Serial.println(String((char *)macaddr));
    }

    sendIdToClient(macaddr);
  }
};

void setup()
{
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);

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
  transactionCounter++;

  SendParamsAction paramsData;
  paramsData.transactionCounter = transactionCounter;
  paramsData.timestamp = micros();
  esp_now_send(broadcastAddr, (uint8_t *)&paramsData, sizeof(SendParamsAction));

  delay(16);
}

#else

SendParamsAction paramsData;

const uint8_t *serverAddr;
int clientId = 0;
bool serverAdded = false;

void handShakeWithServer(const uint8_t *macaddr)
{
  if (!esp_now_is_peer_exist(macaddr))
  // if (!serverAdded)
  {

    esp_now_peer_info_t peerInfo;
    peerInfo.channel = CHANNEL;
    peerInfo.encrypt = false;
    memcpy(peerInfo.peer_addr, macaddr, 6);
    if (esp_now_add_peer(&peerInfo) != ESP_OK)
    {
      Serial.print("Failed to add peer :: ");
      Serial.println(String((char *)macaddr));
      return;
    }

    serverAddr = macaddr;
    serverAdded = true;

    Serial.println("Server ADDED");
  }

  if (serverAdded)
  {
    AssignIdAction data;
    esp_now_send(serverAddr, (uint8_t *)&data, sizeof(data));
  }
}

void recv_cb(const uint8_t *macaddr, const uint8_t *incomingData, int len)
{
  Action action = getActionFromData(incomingData);
  // Serial.print("Acction received :: ");
  // Serial.print(action);
  // Serial.print(" \t from :: ");
  // Serial.println(String((char *)macaddr));

  if (action == ASSIGN_ID)
  {
    AssignIdAction data;
    memcpy(&data, incomingData, sizeof(data));
    clientId = data.id;

    Serial.print("clientId assigned :: ");
    Serial.println(clientId);

    return;
  }
  else if (action == SEND_PARAMS)
  {
    if (clientId == 0)
    {
      handShakeWithServer(macaddr);
      return;
    }

    memcpy(&paramsData, incomingData, sizeof(paramsData));

    // Serial.print("Bytes received: ");
    // Serial.println(len);
    // Serial.print("cnt :: ");
    // Serial.print(paramsData.transactionCounter);
    // Serial.print("\t\t\t\t - ts :: ");
    // Serial.println(paramsData.timestamp);
    // Serial.println("-------------");

    return;
  }
}

void setup()
{
  Serial.begin(115200);

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