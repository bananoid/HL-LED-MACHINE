#ifndef HL_LIB_SSD1327_SSD1327
#define HL_LIB_SSD1327_SSD1327

#include "Arduino.h"
#include "stdint.h"
#include "SPI.h"
#include "font8x8_basic.h"
#include "font16x16.h"
#include "font16x32.h"

#ifndef SSD1327_H
#include "SSD1327.h"
#endif

SSD1327::SSD1327(int cs, int dc, int rst)
{
	_cs = cs;
	_dc = dc;
	_rst = rst;
}

//TODO: Find a way to handle the write commands without toggling CS and DC every time
void SSD1327::writeCmd(uint8_t reg)
{ //Writes a command byte to the driver
	digitalWrite(_dc, LOW);
	digitalWrite(_cs, LOW);
	SPI.transfer(reg);
	digitalWrite(_cs, HIGH);
}

void SSD1327::writeData(uint8_t data)
{ //Writes 1 byte to the display's memory
	digitalWrite(_dc, HIGH);
	digitalWrite(_cs, LOW);
	SPI.transfer(data);
	digitalWrite(_cs, HIGH);
}

void SSD1327::setWriteZone(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2)
{									//defines a rectangular area of memory which the driver will itterate through. This function takes memory locations, meaning a 64x128 space
	writeCmd(0x15); //Set Column Address
	writeCmd(x1);		//Beginning. Note that you must divide the column by 2, since 1 byte in memory is 2 pixels
	writeCmd(x2);		//End

	writeCmd(0x75); //Set Row Address
	writeCmd(y1);		//Beginning
	writeCmd(y2);		//End
}

uint16_t SSD1327::coordsToAddress(uint8_t x, uint8_t y)
{ //Converts a pixel location to a linear memory address
	return (x / 2) + (y * 64);
}

void SSD1327::setPixelChanged(uint8_t x, uint8_t y, bool changed)
{
	uint16_t targetByte = coordsToAddress(x, y) / 8;
	bitWrite(changedPixels[targetByte], coordsToAddress(x, y) % 8, changed);
}

void SSD1327::drawPixel(uint8_t x, uint8_t y, uint8_t color, bool display)
{ //pixel xy coordinates 0-127, color 0-15, and whether to immediately output it to the display or buffer it
	int address = coordsToAddress(x, y);
	if ((x % 2) == 0)
	{ //If this is an even pixel, and therefore needs shifting to the more significant nibble
		frameBuffer[address] = (frameBuffer[address] & 0x0f) | (color << 4);
	}
	else
	{
		frameBuffer[address] = (frameBuffer[address] & 0xf0) | (color);
	}

	if (display)
	{
		setWriteZone(x / 2, y, x / 2, y);
		writeData(frameBuffer[address]);
		setPixelChanged(x, y, false); // We've now synced the display with this byte of the buffer, no need to write it again
	}
	else
	{
		setPixelChanged(x, y, true); // This pixel is due for an update next refresh
	}
}

void SSD1327::drawRect(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t color, bool display)
{															//Draws a rectangle from x1,y1 to x2,y2.
	uint8_t xMin = min(x1, x2); // TODO: double performance by writing whole bytes at a time
	uint8_t xMax = max(x1, x2);
	uint8_t yMin = min(y1, y2);
	uint8_t yMax = max(y1, y2);
	for (uint8_t x = xMin; x <= xMax; x++)
	{
		for (uint8_t y = yMin; y <= yMax; y++)
		{
			drawPixel(x, y, color, display);
		}
	}
}

void SSD1327::drawHLine(int x, int y, int length, uint8_t color, bool display)
{
	for (uint8_t i = x; i < x + length; i++)
	{
		drawPixel(i, y, color, display);
	}
}

void SSD1327::drawVLine(int x, int y, int length, uint8_t color, bool display)
{
	for (uint8_t i = y; i < y + length; i++)
	{
		drawPixel(x, i, color, display);
	}
}

void SSD1327::drawLine(int x0, int y0, int x1, int y1, uint8_t color, bool display)
{ //Bresenham's line algorithm
	int deltaX = abs(x1 - x0);
	int deltaY = abs(y1 - y0);
	int signX = x0 < x1 ? 1 : -1;
	int signY = y0 < y1 ? 1 : -1;
	int error = (deltaX > deltaY ? deltaX : -deltaY) / 2, error2;

	while (true)
	{
		drawPixel(x0, y0, color, display);
		if (x0 == x1 && y0 == y1)
			break;
		error2 = error;
		if (error2 > -deltaX)
		{
			error -= deltaY;
			x0 += signX;
		}
		if (error2 < deltaY)
		{
			error += deltaX;
			y0 += signY;
		}
	}
}

void SSD1327::drawByteAsRow(uint8_t x, uint8_t y, uint8_t byte, uint8_t color)
{ //Draws a byte as an 8 pixel row
	for (int i = 0; i < 8; i++)
	{
		if (bitRead(byte, i))
		{
			drawPixel(x + i, y, color, false);
		}
	}
}

void SSD1327::drawChar(uint8_t x, uint8_t y, char thisChar, uint8_t color)
{
	for (size_t i = 0; i < 8; i++)
	{
		drawByteAsRow(x, y + i, font8x8_basic[(unsigned char)thisChar][i], color);
	}
}

void SSD1327::drawCharArray(uint8_t x, uint8_t y, char text[], uint8_t color, int size)
{
	const char *thisChar;
	uint8_t xOffset = 0;
	if (size == 16)
	{
		for (thisChar = text; *thisChar != '\0'; thisChar++)
		{
			drawChar16(x + xOffset, y, *thisChar, color);
			xOffset += 8;
		}
	}
	else if (size == 32)
	{
		for (thisChar = text; *thisChar != '\0'; thisChar++)
		{
			drawChar32(x + xOffset, y, *thisChar, color);
			xOffset += 16;
		}
	}
	else
	{
		for (thisChar = text; *thisChar != '\0'; thisChar++)
		{
			drawChar(x + xOffset, y, *thisChar, color);
			xOffset += 8;
		}
	}
}

void SSD1327::drawString(uint8_t x, uint8_t y, String textString, uint8_t color, int size)
{
	char text[64];
	textString.toCharArray(text, 64);
	drawCharArray(x, y, text, color, size);
}

void SSD1327::drawChar16(uint8_t x, uint8_t y, char thisChar, uint8_t color)
{
	for (size_t row = 0; row < 16; row++)
	{
		drawByteAsRow(x, y + row, font16x16[(unsigned char)thisChar][row * 2], color);
		drawByteAsRow(x + 8, y + row, font16x16[(unsigned char)thisChar][(row * 2) + 1], color);
	}
}

void SSD1327::drawChar32(uint8_t x, uint8_t y, char thisChar, uint8_t color)
{
	for (size_t row = 0; row < 32; row++)
	{
		drawByteAsRow(x, y + row, font16x32[(unsigned char)thisChar][row * 2], color);
		drawByteAsRow(x + 8, y + row, font16x32[(unsigned char)thisChar][(row * 2) + 1], color);
	}
}

void SSD1327::fillStripes(uint8_t offset)
{ //gradient test pattern
	for (int i = 0; i < 8192; i++)
	{
		uint8_t color = ((i + offset) & 0xF) | (((i + offset) & 0xF) << 4);
		frameBuffer[i] = color;
	}
	for (uint16_t i = 0; i < 1024; i++)
	{
		changedPixels[i] = 0xFF; // Set all pixels to be updated next frame. fillStripes should not be used without a full write anyways, but just in case
	}
}

void SSD1327::setupScrolling(uint8_t startRow, uint8_t endRow, uint8_t startCol, uint8_t endCol, uint8_t scrollSpeed, bool right)
{
	uint8_t swap;
	if (startRow > endRow)
	{ // Ensure start row is before end
		swap = startRow;
		startRow = endRow;
		endRow = swap;
	}
	if (startCol > endCol)
	{ // Ditto for columns
		swap = startCol;
		startCol = endCol;
		endCol = swap;
	}
	writeCmd(0x2E); // Deactivate scrolling before changing anything
	if (right)
	{
		writeCmd(0x26); // Scroll right
	}
	else
	{
		writeCmd(0x27); // Scroll left
	}
	writeCmd(0); // Dummy byte
	writeCmd(startRow);
	writeCmd(scrollSpeed);
	writeCmd(endRow);
	writeCmd(startCol);
	writeCmd(endCol);
	writeCmd(0); // Dummy byte
};

void SSD1327::startScrolling()
{
	writeCmd(0x2F);
}

void SSD1327::stopScrolling()
{
	writeCmd(0x2E);
}

void SSD1327::scrollStep(uint8_t startRow, uint8_t endRow, uint8_t startCol, uint8_t endCol, bool right)
{
	setupScrolling(startRow, endRow, startCol, endCol, SSD1327_SCROLL_2, right);
	startScrolling();
	delay(15);
	stopScrolling();
}

void SSD1327::clearBuffer()
{ //
	for (int i = 0; i < 8192; i++)
	{
		if (frameBuffer[i])
		{ // If there is a non-zero (non-black) byte here, make sure it gets updated
			frameBuffer[i] = 0;
			bitWrite(changedPixels[i / 8], i % 8, 1); // Mark this pixel as needing an update
		}
	}
}

void SSD1327::writeFullBuffer()
{															 //Outputs the full framebuffer to the display
	setWriteZone(0, 0, 63, 127); //Full display
	for (int i = 0; i < 8192; i++)
	{
		writeData(frameBuffer[i]);
	}
	for (uint16_t i = 0; i < 1024; i++)
	{
		changedPixels[i] = 0; // Set all pixels as up to date.
	}
}

void SSD1327::writeUpdates()
{ // Writes only the pixels that have changed to the display
	for (size_t y = 0; y < 128; y++)
	{
		bool continued = false; // If we can continue with the write zone we're using
		for (size_t x = 0; x < 128; x++)
		{
			uint16_t address = coordsToAddress(x, y);
			if (bitRead(changedPixels[address / 8], address % 8))
			{ // If we need an update here
				if (!continued)
				{ // Just write the byte, no new write zone needed
					continued = true;
					setWriteZone(x / 2, y, 63, 127); // Set the write zone for this new byte and any subsequent ones
				}
				writeData(frameBuffer[address]);
				bitWrite(changedPixels[address / 8], address % 8, 0);
			}
			else
			{
				continued = false; // The chain of pixels is broken
			}
		}
	}
}

void SSD1327::setContrast(uint8_t contrast)
{
	writeCmd(0x81);			//set contrast control
	writeCmd(contrast); //Contrast byte
}

void SSD1327::initRegs()
{									//Sends all the boilerplate startup and config commands to the driver
	writeCmd(0xae); //--turn off oled panel

	writeCmd(0x15); //set column addresses
	writeCmd(0x00); //start column  0
	writeCmd(0x7f); //end column  127

	writeCmd(0x75); //set row addresses
	writeCmd(0x00); //start row  0
	writeCmd(0x7f); //end row  127

	writeCmd(0x81); //set contrast control
	writeCmd(0x80); //50% (128/255)

	writeCmd(0xa0); //gment remap
	writeCmd(0x51); //51 (To my understanding, this is orientation

	writeCmd(0xa1); //start line
	writeCmd(0x00);

	writeCmd(0xa2); //display offset
	writeCmd(0x00);

	writeCmd(0xa4); //rmal display
	writeCmd(0xa8); //set multiplex ratio
	writeCmd(0x7f);

	writeCmd(0xb1); //set phase leghth
	writeCmd(0xf1);

	writeCmd(0xb3); //set dclk
	writeCmd(0x00); //80Hz:0xc1 90Hz:0xe1  100Hz:0x00  110Hz:0x30 120Hz:0x50  130Hz:0x70   01

	writeCmd(0xab); //Enable vReg
	writeCmd(0x01);

	writeCmd(0xb6); //set phase leghth
	writeCmd(0x0f);

	writeCmd(0xbe); //Set vcomh voltage
	writeCmd(0x0f);

	writeCmd(0xbc); //set pre-charge voltage
	writeCmd(0x08);

	writeCmd(0xd5); //second precharge period
	writeCmd(0x62);

	writeCmd(0xfd); //Unlock commands
	writeCmd(0x12);

	writeCmd(0xAF);
	delay(300);
}

void SSD1327::init()
{
	pinMode(_cs, OUTPUT);
	pinMode(_dc, OUTPUT);
	pinMode(_rst, OUTPUT);

	SPI.setDataMode(SPI_MODE0);
	SPI.setBitOrder(MSBFIRST);
	SPI.setClockDivider(SPI_CLOCK_DIV2);
	SPI.begin();

	digitalWrite(_rst, HIGH); //Reset display
	delay(100);
	digitalWrite(_rst, LOW);
	delay(100);
	digitalWrite(_rst, HIGH);
	delay(100);

	initRegs();
}
#endif /* HL_LIB_SSD1327_SSD1327 */
