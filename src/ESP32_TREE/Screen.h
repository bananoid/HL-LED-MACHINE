#pragma once

class Screen
{
public:
  Screen();
  void begin();
  void sayHello(uint line);

  void print(String message, uint line);
  void clear();
  void displayScreen();
  // String header;
};