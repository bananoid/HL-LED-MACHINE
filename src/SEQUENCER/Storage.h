#pragma once

#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

#include "config.h"
#include <TaskSchedulerDeclarations.h>

#define SDCARD_CS_PIN BUILTIN_SDCARD
#define SDCARD_MOSI_PIN 11 // not actually used
#define SDCARD_SCK_PIN 13  // not actually used

#define DATA_FILE_NAME "SEQDATA.bin"

class Storage
{
private:
public:
  File frec;
  Task autoSaveTask;
  // unsigned long autoSaveTime = 0;

  void begin(Scheduler *runner)
  {
    // autoSaveTask.set(TASK_SECOND, TASK_FOREVER, [this]()
    //                  { autoSave(); });
    // runner->addTask(autoSaveTask);
    // autoSaveTask.disable();
  }

  bool checkSDCard()
  {
    if (!SD.begin(BUILTIN_SDCARD))
    {
      Serial.println("Card failed, or not present");
      return false;
    }
    return true;
  }
  void load(uint8_t *data, int size)
  {
    if (!checkSDCard())
    {
      return;
    }

    File file = SD.open(DATA_FILE_NAME, FILE_READ);
    if (!file)
    {
      Serial.print("File not found ");
      Serial.println(DATA_FILE_NAME);
      return;
    }

    file.readBytes(data, size);

    file.close();
  }

  void save(uint8_t *data, int size)
  {
    unsigned long curTime = micros();

    if (SD.exists(DATA_FILE_NAME))
    {
      SD.remove(DATA_FILE_NAME);
    }

    frec = SD.open(DATA_FILE_NAME, FILE_WRITE);

    frec.write(data, size);

    frec.close();

    long deltaTime = micros() - curTime;

    Serial.printf("Save in %ius\n", deltaTime);
  }

  // void autoSave()
  // {
  //   autoSaveTime = millis();
  // }
};

extern Storage *storage;
