#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "Screen.h"

#define OLED_RESET 4     // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

Screen::Screen()
{
}

void Screen::begin()
{
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextSize(1);
  display.setTextColor(WHITE);
}

void Screen::clear()
{
  display.clearDisplay();
}

void Screen::displayScreen()
{
  display.display();
}

void Screen::sayHello(uint line)
{
  display.setCursor(0, line);
  display.printf("hello %i", random(0, 50));
};

void Screen::print(String message, uint line)
{
  display.setCursor(0, line);
  display.println(message);
};
