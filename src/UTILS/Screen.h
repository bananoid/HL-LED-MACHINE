#pragma once
#include "AOYAMA_TREE/COMMON/config.h"
#include <TaskSchedulerDeclarations.h>

class Screen : public Task
{
public:
  Screen(Scheduler *runner);
  void begin();
  void sayHello(uint line);

  void print(String message, uint line);
  void clear();
  void displayScreen();

  bool invalid = false;

  // Task
  bool Callback(); // this is the function called from the task
};