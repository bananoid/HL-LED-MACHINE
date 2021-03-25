#pragma once

// #include <TaskSchedulerDeclarations.h>
// #include <TaskScheduler.h>

// #define _TASK_STD_FUNCTION
// #define _TASK_OO_CALLBACKS

class Screen
// class Screen : public Task
{
public:
  Screen();
  void begin();
  void sayHello(uint line);

  void print(String message, uint line);
  void clear();
  void displayScreen();

  bool invalid = false;

  // Task
  // bool Callback(); // this is the function called from the task
};