#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "OledScreen.h"

#define OLED_RESET 4     // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

OledScreen::OledScreen(int nLines, int lineLen)
{
  this->nLines = nLines;
  this->lineLen = lineLen;
  lines.reserve(nLines);
}

void OledScreen::begin()
{
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.clearDisplay();
}

void OledScreen::clearScreen()
{
  display.clearDisplay();
}

void OledScreen::displayScreen()
{
  // task that displays the buffer
  if (!invalid)
  {
    return;
  }

  invalid = false;
  clearScreen();
  for (int line = 0; line < nLines; line++)
  {
    display.setCursor(0, 8 * line);
    display.println(lines[line]);
  }
  display.display();
}

void OledScreen::sayHello(uint line)
{
  println("hello " + String(random(0, 99)), line);
};

void OledScreen::println(String message, uint line)
{
  invalid = true;
  lines[line] = message.substring(0, lineLen);
};