#include "UIOlend128x128.h"

#include <Arduino.h>
#include <SPI.h>
#include <ssd1351.h>

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

  display.fillScreen(ssd1351::RGB());

  for (int x = 0; x < 128; x++)
  {
    float fm = sinf(x * 0.01524 + t * 0.1235) * 10;

    float s = sinf(x * 0.005 * fm + t);
    s = asinf(s) / HALF_PI * 0.2 + 0.5;

    display.drawLine(x, 128, x, (s)*128, ssd1351::RGB(255, x * 2, x * 2));
  }

  display.updateScreen();
}

UIOled128x128 *uiOled128x128 = new UIOled128x128();