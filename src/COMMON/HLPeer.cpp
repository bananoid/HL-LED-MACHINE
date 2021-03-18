#include <WiFi.h>
#include "HLPeer.h"
#include "Messages.h"
#include "Boards.h"

HLPeer *HLPeerSingleton = new HLPeer();

void HLPeer::getOwnBoardInformation()
{
  boardInfo = getBoardInfo(WiFi.macAddress());
}

// void HLPeer::displayHeader()
// {
//   String line1 = boardInfo.boardName;
//   String line2 = boardInfo.macAddress;
//   // screen->print(line1, 0);
//   // screen->print(line2, 8);
// }

BaseMessage HLPeer::getRandomMessage()
{
  BaseMessage msg;
  msg.messageType = FLOWER_TOUCH;
  msg.targetId = 1;
  msg.sourceId = boardInfo.boardId;
  return msg;
}

HLPeer::HLPeer()
{
  getOwnBoardInformation();
}

BaseMessage myData;

void HLPeer::onDataReceived(const uint8_t *mac, const uint8_t *incomingData, int len)
{
  // TODO access own ID

  uint8_t messageType = getActionTypeFromData(incomingData);
  uint targetId;
  uint sourceId;

  // Serial.println("Receiving Message!");
  String messageTypeName;

  switch (messageType)
  {

  case PING:
  {
    BaseMessage pingMessage;
    memcpy(&pingMessage, incomingData, sizeof(pingMessage));
    targetId = pingMessage.targetId;
    sourceId = pingMessage.sourceId;
    messageTypeName = "ping";
    break;
  }
  case FLOWER_TOUCH:
  {
    FlowerTouchMessage flowerTouchMessage;
    memcpy(&flowerTouchMessage, incomingData, sizeof(flowerTouchMessage));
    targetId = flowerTouchMessage.targetId;
    sourceId = flowerTouchMessage.sourceId;
    messageTypeName = "flower touch";
    break;
  }
  case FLOWER_LED:
  {
    FlowerLedMessage flowerLedMessage;
    memcpy(&flowerLedMessage, incomingData, sizeof(flowerLedMessage));
    targetId = flowerLedMessage.targetId;
    sourceId = flowerLedMessage.sourceId;
    messageTypeName = "flower LED";
    break;
  }
  case BRANCH_STATE:
  {
    BranchStateMessage branchStateMessage;
    memcpy(&branchStateMessage, incomingData, sizeof(branchStateMessage));
    targetId = branchStateMessage.targetId;
    sourceId = branchStateMessage.sourceId;
    messageTypeName = "branch state";
    break;
  }
  default:
    targetId = -1;
    sourceId = -1;
    messageTypeName = "UNKNOWN";
    break;
  }

  // Serial.println("\tReceived a message type: " + messageTypeName);
  // Serial.println("\tcoming from: " + String(sourceId) + ", directed to " + String(targetId));
}

void HLPeer::beginServer()
{
  // Screen *screen = new Screen();
  // screen->begin();

  esp_now_register_recv_cb(onDataReceived);
}

void HLPeer::ping()
{

  BaseMessage message = getRandomMessage();

  Serial.println(boardInfo.boardName + ": Ping!");
  broadcastData((uint8_t *)&message, sizeof(BaseMessage));

  // screen->clear();
  // displayHeader();
  // screen->sayHello(16);
  // screen->print("MSG->B" + String(message.targetId) + " [TYPE:" + String(message.messageType) + "]", 24);
  // screen->displayScreen();
}

// TODO
// ?? function to update screen (receive and sending areas)