#pragma once
#include "Storage.h"
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <Arduino.h>
#include "FileTools.h"
#include <map>

class SortageBank
{
public:
  String dirPath;
  String filePrefix;
  std::map<uint16_t, FileEntry> entries;

  uint16_t currentSlot = 0;
  uint16_t maxNumOfSlots = 256;

  SortageBank(String dirPath, String filePrefix)
  {
    this->dirPath = dirPath;
    this->filePrefix = filePrefix;
  }

  String getFilePahtForSlot(uint16_t slotNumber)
  {
    return this->dirPath + "/" + this->filePrefix + slotNumber;
  }

  void readSlots()
  {
    entries.clear();
    FileTools::readSlots(&entries, this->dirPath, this->filePrefix);

    // for (auto const &e : entries)
    // {
    //   Serial.printf("Slot %i\t\t%s\n", e.first, e.second.name.c_str());
    // }
  }

  void saveSlot(uint8_t *data, int size, uint16_t slotNumber)
  {
    String filePath = getFilePahtForSlot(slotNumber);
    FileTools::save(data, size, filePath.c_str());

    readSlots();
  }

  void saveSlot(uint8_t *data, int size)
  {
    saveSlot(data, size, currentSlot);
    currentSlot++; //TMP
  }

  void loadSlot(uint8_t *data, int size, uint16_t slotNumber)
  {
    String filePath = getFilePahtForSlot(slotNumber);
    FileTools::load(data, size, filePath.c_str());
  }

  void loadSlot(uint8_t *data, int size)
  {
    loadSlot(data, size, currentSlot);
  }
};