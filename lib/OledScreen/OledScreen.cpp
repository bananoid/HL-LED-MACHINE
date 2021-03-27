#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "OledScreen.h"

#define OLED_RESET 4     // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// #define OLEDSCREEN_DISABLED

#ifndef OLEDSCREEN_DISABLED
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
#endif

OledScreen::OledScreen(int nLines, int lineLen)
{
#ifndef OLEDSCREEN_DISABLED
  this->nLines = nLines;
  this->lineLen = lineLen;
  lines.reserve(nLines);
#endif
}

void OledScreen::begin()
{
#ifndef OLEDSCREEN_DISABLED
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.clearDisplay();
#endif
}

void OledScreen::clearScreen()
{
#ifndef OLEDSCREEN_DISABLED
  display.clearDisplay();
#endif
}

void OledScreen::displayScreen()
{
#ifndef OLEDSCREEN_DISABLED
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
#endif
}

void OledScreen::sayHello(uint line)
{
#ifndef OLEDSCREEN_DISABLED
  println("hello " + String(random(0, 99)), line);
#endif
};

void OledScreen::println(String message, uint line)
{
#ifndef OLEDSCREEN_DISABLED
  invalid = true;
  lines[line] = message.substring(0, lineLen);
#endif
};
