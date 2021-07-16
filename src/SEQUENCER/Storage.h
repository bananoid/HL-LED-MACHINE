#pragma once

#include <Arduino.h>

#include "config.h"
#include <TaskSchedulerDeclarations.h>

#define SDCARD_CS_PIN BUILTIN_SDCARD
#define SDCARD_MOSI_PIN 11 // not actually used
#define SDCARD_SCK_PIN 13  // not actually used

#define DATA_FILE_NAME "SEQDATA.bin"

#define PROJECTS_PATH "PROJECTS"
#define PROJECTS_PREFIX "PROJ_"

#define TRACKS_PATH "TRACKS"
#define TRACKS_PREFIX "TRACK_"

#include "FilesStoreStructures.h"

#include <Parameter.h>
#include "StorageBanck.h"

class Storage
{
private:
public:
  // unsigned long autoSaveTime = 0;

  SortageBank *projectsBank;
  SortageBank *tracksBank;

  Storage()
  {
    projectsBank = new SortageBank(PROJECTS_PATH, PROJECTS_PREFIX);
    tracksBank = new SortageBank(TRACKS_PATH, TRACKS_PREFIX);
  }

  void begin(Scheduler *runner)
  {
    // autoSaveTask.set(TASK_SECOND, TASK_FOREVER, [this]()
    //                  { autoSave(); });
    // runner->addTask(autoSaveTask);
    // autoSaveTask.disable();

    // projectsBank->readSlots();
    // tracksBank->readSlots();
  }
};

extern Storage *storage;
