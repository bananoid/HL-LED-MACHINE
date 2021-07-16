#pragma once

#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <map>

struct FileEntry
{
  uint16_t slot;
  String name;
};

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

    // unsigned long curTime = micros();

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

  static uint16_t slotFromFilePath(String name, String prefix)
  {
    auto nInx = prefix.length();
    auto nStr = name.substring(nInx);
    auto slot = nStr.toInt();

    // Serial.printf("%s\tnInx:%i\tnStr:%s\t%i\n", name.c_str(), nInx, nStr.c_str(), slot);
    return slot;
  }

  static void readSlots(std::map<uint16_t, FileEntry> *entries, String dirPath, String prefix)
  {
    if (!checkSDCard())
    {
      return;
    }

    File root = SD.open(dirPath.c_str());
    root.rewindDirectory();

    uint16_t slot = 0;
    while (true)
    {
      File entry = root.openNextFile();
      if (!entry)
      {
        break;
      }
      String entryName = (String)entry.name();

      slot = slotFromFilePath(entryName, prefix);

      entries->insert({slot, {slot, entryName}});

      entry.close();
    }

    root.close();
  }
};