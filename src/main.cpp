#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>

#define IS_SERVER // Comment for client mode

#define CHANNEL 3

uint8_t broadcastAddr[] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff}; // ALL RECEIVERS

//Server mac :: 16::82::28::102::150::204

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

// Client ID start from 1
void sendIdToClient(const uint8_t *macaddr)
{

  AssignIdAction data;
  data.id = clientsIdCounter + 1;
  for (int i = 0; i < MAX_NUM_CLIENT; i++)
  {
    if (clientsList[i] == macaddr)
    {
      data.id = i;
    }
  }

  esp_err_t result = esp_now_send(macaddr, (uint8_t *)&data, sizeof(data));

  Serial.print("Send id :: ");
  Serial.print(data.id);
  Serial.print(" to client :: ");
  printMacAddr(macaddr);

  if (result == ESP_OK)
  {
    Serial.println("Sent with success");
  }
  else
  {
    Serial.println("Error sending the data");
    return;
  }

  clientsList[data.id] = macaddr;

  clientsIdCounter = data.id;
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
      printMacAddr(macaddr);
    }
  }

  if (action == ASSIGN_ID)
  {
    sendIdToClient(macaddr);
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
  esp_now_register_send_cb(send_cb);

  // esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  // esp_now_

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

const uint8_t *serverAddr = nullptr;
int clientId = 0;
bool serverAdded = false;

void addServerToPeers()
{
  // if (!serverAdded)
  if (serverAddr == nullptr)
  {
    return;
  }

  if (!esp_now_is_peer_exist(serverAddr))
  {

    esp_now_peer_info_t peerInfo;
    peerInfo.channel = CHANNEL;
    peerInfo.encrypt = false;
    memcpy(peerInfo.peer_addr, serverAddr, 6);
    if (esp_now_add_peer(&peerInfo) != ESP_OK)
    {
      Serial.print("Failed to add peer :: ");
      printMacAddr(serverAddr);
      // delay(500);
      return;
    }

    serverAdded = true;

    Serial.print("\nServer ADDED");
    printMacAddr(serverAddr);
    Serial.println("-------");
  }
}

void handShakeWithServer(const uint8_t *macaddr)
{
  addServerToPeers();

  serverAddr = macaddr;

  if (serverAdded)
  {
    AssignIdAction data;
    data.action = ASSIGN_ID;
    esp_now_send(serverAddr, (uint8_t *)&data, sizeof(data));
  }
}

void recv_cb(const uint8_t *macaddr, const uint8_t *incomingData, int len)
{
  Action action = getActionFromData(incomingData);
  // Serial.print("Acction received :: ");
  // Serial.print(action);
  // Serial.print(" \t from :: ");
  // printMacAddr(macaddr);

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