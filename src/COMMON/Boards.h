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

typedef struct board_info
{
  int boardId;
  String macAddress;
  board_type boardType;
  String boardTypeName;
  String boardName;

} board_info;

// extern board boards[] = {"3C:61:05:2E:85:74", "Tree", TREE};
board_info getBoardInfo(String macAddress);