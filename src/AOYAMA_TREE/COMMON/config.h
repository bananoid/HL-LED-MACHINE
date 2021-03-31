#pragma once

// #define _TASK_OO_CALLBACKS
// #define _TASK_STD_FUNCTION

#define WIFI_CHANNEL 1

// Serial Messenger Teensy-ESP32
// #define BAUD_RATE 115200
#define BAUD_RATE 921600

#define PEER_TYPES GATEWAY, FLOWER
#define N_PEERS 10

#define NUMBER_OF_FLOWERS 5

#define PEER_LIST                                 \
  {                                               \
    {"3C:61:05:2F:B7:E0", "Gateway", GATEWAY},    \
        {"24:0A:C4:EC:9A:A0", "Flower", FLOWER},  \
        {"3C:61:05:2B:01:04", "Flower", FLOWER},  \
        {"3C:61:05:16:AE:E8", "Flower", FLOWER},  \
        {"3C:61:05:2A:A0:50", "Flower", FLOWER},  \
        {"3C:61:05:2E:85:74", "Flower", FLOWER},  \
        {"9C:9C:1F:C9:C6:5C", "Tunnel", FLOWER},  \
        {"24:0A:C4:EE:E0:E8", "Tunnel", FLOWER},  \
        {"3C:61:05:28:E4:D4", "Costume", FLOWER}, \
    {                                             \
      "3C:61:05:2F:A9:7C", "Costume", FLOWER      \
    }                                             \
  }

#define FLOWER_PEER_IDS {1, 2, 3, 4, 5};