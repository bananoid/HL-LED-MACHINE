#include "UIOlend128x128.h"

#include <Arduino.h>
#include <SPI.h>
#include <ssd1351.h>
#include "GFX_fonts/Font5x7FixedMono.h"

//typedef ssd1351::IndexedColor Color;
// typedef ssd1351::LowColor Color;
typedef ssd1351::HighColor Color;

// auto display = ssd1351::SSD1351<Color, ssd1351::NoBuffer, 128, 96>();
auto display = ssd1351::SSD1351<Color, ssd1351::SingleBuffer, 128, 128>();
// auto display = ssd1351::SSD1351<Color, ssd1351::DoubleBuffer, 128, 128>();

void UIOled128x128::begin()
{
  display.begin();
}

void UIOled128x128::update()
{

  float t = micros() / 300000.0;

  display.fillScreen(ssd1351::RGB(255, 200, 200));

  display.fillCircle(10, 50, 16, ssd1351::RGB(255, 120, 100));
  display.fillCircle(128 - 10, 50, 16, ssd1351::RGB(255, 120, 100));
  display.fillCircle(10, 50, 7, ssd1351::RGB(255, 80, 70));
  display.fillCircle(128 - 10, 50, 7, ssd1351::RGB(255, 80, 70));

  for (int x = 0; x < 128; x++)
  {
    float fm = sinf(x * 0.01524 + t * 0.1235) * 10;

    float s = sinf(x * 0.005 * fm + t);
    s = asinf(s) / HALF_PI * 0.2 + 0.5;

    display.drawLine(x, 128, x, (s)*128, ssd1351::RGB(255, 180, 180));
    // display.drawPixel(x, (s)*128 + 20, ssd1351::RGB(255, 0, 0));
  }

  // display.drawRoundRect(10, 10, 128 - 20, 128 - 20, 20, ssd1351::RGB(0, 100, 255));

  display.setFont(Font5x7FixedMono);
  display.setTextSize(1);
  display.setCursor(20, 100);
  display.setTextColor(ssd1351::RGB(30, 30, 30));
  display.print(t);
  display.setCursor(20, 120);
  display.setTextColor(ssd1351::RGB(30, 30, 30));
  display.setTextSize(2);
  display.print("NIPPLES");

  display.updateScreen();
}

UIOled128x128 *uiOled128x128 = new UIOled128x128();