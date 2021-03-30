#pragma once
// task definition

#define ARDUINO_ARCH_ESP32 // This is to make TaskScheduler _TASK_STD_FUNCTION work on teensy
// #define _TASK_OO_CALLBACKS
#define _TASK_STD_FUNCTION
#define _TASK_MICRO_RES

// Serial Messenger
#define BAUD_RATE 115200

// #define NUMBER_OF_INSTRUMENTS 3

// #define ENCODER_PIN_A 18
// #define ENCODER_PIN_B 17
// #define ENCODER_PIN_BUTTON 16
// #define LED_PIN 22
// #define NUM_LEDS 16
// #define NUM_LED_STRIPES 1

// const int instrumentPins[NUMBER_OF_INSTRUMENTS] = {13, 14, 15};
// const int buttonPins[NUMBER_OF_INSTRUMENTS] = {19, 20, 21};
