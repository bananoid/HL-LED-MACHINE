#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "OledScreen.h"

#define OLED_RESET 4     // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

OledScreen::OledScreen()
{
}

void OledScreen::begin()
{
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextSize(1);
  display.setTextColor(WHITE);
}

void OledScreen::clear()
{
  display.clearDisplay();
}

void OledScreen::displayScreen()
{
  display.display();
}

void OledScreen::sayHello(uint line)
{
  print("hello " + String(random(0, 50)), line);
};

void OledScreen::print(String message, uint line)
{
  // invalid = true;
  line = line * 8;
  display.setCursor(0, line);
  display.setTextColor(BLACK);
  display.println("                      ");
  display.setCursor(0, line);
  display.setTextColor(WHITE);
  display.println(message);
  display.display();
};
