#include "Tree.h"

Tree *TreeSingleton = new Tree();

void Tree::sendFlowerTouchMessage(FlowerTouchMessage message, int boardId)
{
  Serial.println("Sending Flower Touch Message to board " + String(boardId));
  broadcastData((uint8_t *)&message, sizeof(FlowerTouchMessage));
}