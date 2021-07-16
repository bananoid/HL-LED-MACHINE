#pragma once
#include "Storage.h"
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <Arduino.h>
#include "FileTools.h"

class SortageBank
{
public:
  String dirPath;
  String filePrefix;

  SortageBank(String dirPath, String filePrefix)
  {
    this->dirPath = dirPath;
    this->filePrefix = filePrefix;
  }

  String getFilePahtForSlot(uint16_t slotNumber)
  {
    return String(this->dirPath) + "/" + String(this->filePrefix) + slotNumber;
  }

  void loadBanck()
  {
    if (!FileTools::checkSDCard())
    {
      return;
    }

    File root = SD.open(this->dirPath.c_str());
    root.rewindDirectory();

    while (true)
    {
      File entry = root.openNextFile();
      if (!entry)
      {
        Serial.println("...");
        break;
      }
      String entryName = (String)entry.name();
      Serial.println("FOUND: " + entryName);
      entry.close();
    }

    root.close();
  }

  void saveSlot(uint8_t *data, int size, uint16_t slotNumber = 0)
  {
    String filePath = getFilePahtForSlot(slotNumber);
    FileTools::save(data, size, filePath.c_str());
  }

  void loadSlot(uint8_t *data, int size, uint16_t slotNumber = 0)
  {
    String filePath = getFilePahtForSlot(slotNumber);
    FileTools::load(data, size, filePath.c_str());
  }
};