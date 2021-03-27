#pragma once

// #define _TASK_OO_CALLBACKS
// #define _TASK_STD_FUNCTION

#define WIFI_CHANNEL 1

// Serial Messenger Teensy-ESP32
#define BAUD_RATE 115200

#define PEER_TYPES GATEWAY, FLOWER
#define N_PEERS 4

#define PEER_LIST                                \
  {                                              \
    {"3C:61:05:2F:B7:E0", "Gateway", GATEWAY},   \
        {"24:0A:C4:EC:9A:A0", "Flower", FLOWER}, \
        {"3C:61:05:2A:A0:50", "Flower", FLOWER}, \
    {                                            \
      "3C:61:05:2B:01:04", "Flower", FLOWER      \
    }                                            \
  }
// {"3C:61:05:2E:85:74", "Flower", FLOWER},

#define OLEDSCREEN_DISABLED