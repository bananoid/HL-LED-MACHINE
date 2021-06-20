#pragma once

#include <ssd1351.h>
typedef ssd1351::HighColor Color;
typedef ssd1351::SSD1351<Color, ssd1351::SingleBuffer, 128, 128> Display;