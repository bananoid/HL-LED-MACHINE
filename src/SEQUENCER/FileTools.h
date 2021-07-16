#pragma once

#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

class FileTools
{
private:
public:
  FileTools(/* args */);
  static bool checkSDCard()
  {
    if (!SD.begin(BUILTIN_SDCARD))
    {
      Serial.println("Card failed, or not present");
      return false;
    }
    return true;
  }

  static void load(uint8_t *data, int size, const char *filePath)
  {
    // unsigned long curTime = micros();

    if (!checkSDCard())
    {
      return;
    }

    File file = SD.open(filePath, FILE_READ);
    if (!file)
    {
      Serial.print("File not found ");
      Serial.println(filePath);
      return;
    }

    file.readBytes(data, size);

    file.close();

    // long deltaTime = micros() - curTime;
    // Serial.printf("Load in %ius\n", deltaTime);
  }

  static void save(uint8_t *data, int size, const char *filePath)
  {
    if (!checkSDCard())
    {
      return;
    }

    unsigned long curTime = micros();

    if (SD.exists(filePath))
    {
      SD.remove(filePath);
    }

    File file = SD.open(filePath, FILE_WRITE);

    file.write(data, size);

    file.close();

    // long deltaTime = micros() - curTime;
    // Serial.printf("Save in %ius size:%i\n", deltaTime, size);
  }

  void readStorage()
  {
    if (!checkSDCard())
    {
      return;
    }

    File root = SD.open("/");
    root.rewindDirectory();

    while (true)
    {
      File entry = root.openNextFile();
      if (!entry)
      {
        Serial.println("...");
        // no more files
        break;
      }
      // convert to string to make it easier to work with...
      String entryName = (String)entry.name();
      Serial.println("FOUND: " + entryName);
      entry.close();
    }

    root.close();
  }
};