#include "UI.h"

#include "UIComponents.h"

#include <Arduino.h>
#include <SPI.h>

#include <ssd1351.h>

//typedef ssd1351::IndexedColor Color;
// typedef ssd1351::LowColor Color;
typedef ssd1351::HighColor Color;
typedef ssd1351::SSD1351<Color, ssd1351::SingleBuffer, 128, 128> Display;

// auto display = ssd1351::SSD1351<Color, ssd1351::NoBuffer, 128, 96>();
auto display = Display();
// auto display = ssd1351::SSD1351<Color, ssd1351::DoubleBuffer, 128, 128>();

void UI::begin(Scheduler *runner)
{
  display.begin();

  leftEncoder = new Encoder(ENCODER_LEFT_PIN_A, ENCODER_LEFT_PIN_B);
  rightEncoder = new Encoder(ENCODER_RIGHT_PIN_A, ENCODER_RIGHT_PIN_B);

  updateTask.set(TASK_MILLISECOND * 16, TASK_FOREVER, [this]()
                 {
                   ui->update();
                   ui->draw();
                 });
  runner->addTask(updateTask);
  updateTask.enable();

  leftEncoderButton = new Bounce();
  leftEncoderButton->attach(ENCODER_LEFT_PIN_SW, INPUT);
  leftEncoderButton->interval(25);

  rightEncoderButton = new Bounce();
  rightEncoderButton->attach(ENCODER_RIGHT_PIN_SW, INPUT);
  rightEncoderButton->interval(25);
}

void UI::update()
{
  leftEncoderButton->update();
  rightEncoderButton->update();
}

void UI::draw()
{
  display.fillScreen(ssd1351::RGB(0, 0, 0));

  UIComponents::ParamState state;
  state.value = leftEncoder->read() / 4;
  state.label = "events";
  uint cols = 128 / state.w;
  uint rows = 128 / state.h;
  for (uint yi = 0; yi < rows; yi++)
  {
    for (uint xi = 0; xi < cols; xi++)
    {
      state.x = xi * state.w;
      state.y = yi * state.h;
      state.value += (sinf(xi * yi) * 0.5 + 0.5) * 10;
      UIComponents::drawParam(&display, state);
    }
  }

  display.updateScreen();
}

UI *ui = new UI();