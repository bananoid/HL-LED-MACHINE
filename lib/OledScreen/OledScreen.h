#pragma once

class OledScreen
{
public:
  OledScreen();
  void begin();
  void sayHello(uint line);

  void print(String message, uint line);
  void clear();
  void displayScreen();

};