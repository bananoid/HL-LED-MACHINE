#pragma once

#include "COMMON/HLPeer.h"
#include "COMMON/Messages.h"

class Tree : public HLPeer
{
private:
public:
  void sendFlowerTouchMessage(FlowerTouchMessage message, int boardId);
};

extern Tree *TreeSingleton;