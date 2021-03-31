#pragma once

#ifndef ARDUINO_ARCH_ESP32
#define ARDUINO_ARCH_ESP32 // This is to make TaskScheduler _TASK_STD_FUNCTION work on teensy
#endif

#define _TASK_STD_FUNCTION
#define _TASK_MICRO_RES
