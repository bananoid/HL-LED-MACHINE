#pragma once

// task definition
#define ARDUINO_ARCH_ESP32 // This is to make TaskScheduler _TASK_STD_FUNCTION work on teensy
#define _TASK_STD_FUNCTION
#define _TASK_MICRO_RES

#define KEY_ID_SCREEN_A 1
#define KEY_ID_SCREEN_B 2
#define KEY_ID_SCREEN_C 3
#define KEY_ID_SCREEN_D 4
#define KEY_ID_FRONT_LEFT 5
#define KEY_ID_FRONT_RIGHT 6
#define KEY_ID_WHEEL_LEFT 7
#define KEY_ID_WHEEL_RIGHT 8

#define WHEEL_ID_RIGHT 1
#define WHEEL_ID_LEFT 2