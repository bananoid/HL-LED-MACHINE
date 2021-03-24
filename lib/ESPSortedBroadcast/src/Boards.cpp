#include <Arduino.h>
#include "Boards.h"

// TODO define outside
// board boards[1] = {
//     {"3C:61:05:2E:85:74", "Tree", TREE},
// {"24:0A:C4:ED:92:0C", "Flower", FLOWER},
// {"3C:61:05:2F:A9:7C", "Flower", FLOWER},
// {"3C:61:05:2B:01:05", "Solenoid", SOLENOID},
// };

board_info getBoardInfo(String macAddress, board *boardList)
{
  board_info boardInfo;

  for (int i = 0; i < 5; i++)
  {
    if (macAddress == boardList[i].macAddress)
    {
      boardInfo.boardId = i + 1;
      boardInfo.macAddress = macAddress;
      boardInfo.boardType = boardList[i].boardType;
      boardInfo.boardTypeName = boardList[i].boardTypeName;
      boardInfo.boardName = "B" + String(boardInfo.boardId) + " [" + boardInfo.boardTypeName + "]";
      return boardInfo;
    }
  }
}
