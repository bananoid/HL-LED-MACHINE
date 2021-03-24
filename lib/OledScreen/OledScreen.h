#pragma once
#include <vector>

class OledScreen
{
public:
  OledScreen(int nLines, int lineLen);

  void begin();
  void sayHello(uint line);

  // void print(String message, uint line);
  void println(String message, uint line);
  void clearScreen();
  void displayScreen();

  int nLines;
  int lineLen;

  bool invalid;

  std::vector<String> lines;
};