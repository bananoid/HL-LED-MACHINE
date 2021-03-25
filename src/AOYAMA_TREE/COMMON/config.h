#pragma once

// #define _TASK_OO_CALLBACKS
// #define _TASK_STD_FUNCTION

#define WIFI_CHANNEL 1

// Serial Messenger Teensy-ESP32
#define BAUD_RATE 115200

#define PEER_TYPES TREE, FLOWER, BRANCH, ROCK

#define N_PEERS 3

#define PEER_LIST                                \
  {                                              \
    {"3C:61:05:2A:A0:50", "Gateway", TREE},      \
        {"AC:67:B2:2C:76:E0", "Branch", BRANCH}, \
        {"3C:61:05:2E:85:74", "Flower", FLOWER}, \
  }
