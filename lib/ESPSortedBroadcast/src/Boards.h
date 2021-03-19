#pragma once

#define BOARD_TYPES TREE, FLOWER, BRANCH, ROCK

typedef enum BoardTypes
{
  BOARD_TYPES
} board_type;

typedef struct Board
{
  String macAddress;
  String boardTypeName;
  board_type boardType;
} board;

typedef struct BoardInfo
{
  int boardId;
  String macAddress;
  board_type boardType;
  String boardTypeName;
  String boardName;
} board_info;

board_info getBoardInfo(String macAddress, Board *boardList);