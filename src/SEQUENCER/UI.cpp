#include "UI.h"

#include <Arduino.h>
#include <SPI.h>

auto display = Display();

void UI::begin(Scheduler *runner, Tracker *tracker)
{
  this->tracker = tracker;
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

  leftEncoderButton = new Bounce2::Button();
  leftEncoderButton->attach(ENCODER_LEFT_PIN_SW, INPUT);
  leftEncoderButton->interval(5);

  rightEncoderButton = new Bounce2::Button();
  rightEncoderButton->attach(ENCODER_RIGHT_PIN_SW, INPUT);
  rightEncoderButton->interval(5);

  for (uint8_t i = 0; i < NUM_SCREEN_BTN; i++)
  {
    screenBtns[i] = new Bounce2::Button();
    screenBtns[i]->attach(screenBtnPins[i], INPUT_PULLUP);
    screenBtns[i]->interval(5);
  }

  frontLeftButton = new Bounce2::Button();
  frontLeftButton->attach(FRONT_LEFT_BTN_PIN, INPUT_PULLUP);
  frontLeftButton->interval(5);

  frontRightButton = new Bounce2::Button();
  frontRightButton->attach(FRONT_RIGHT_BTN_PIN, INPUT_PULLUP);
  frontRightButton->interval(5);

  pinMode(FRONT_LEFT_LED_PIN, OUTPUT);
  pinMode(FRONT_RIGHT_LED_PIN, OUTPUT);
}

void UI::update()
{
  leftEncoderButton->update();
  rightEncoderButton->update();

  for (uint8_t i = 0; i < NUM_SCREEN_BTN; i++)
  {
    screenBtns[i]->update();
  }

  frontLeftButton->update();
  frontRightButton->update();
}

void UI::draw()
{
  display.fillScreen(ssd1351::RGB(0, 0, 0));

  // UIComponents::ParamState state;
  // state.value = leftEncoder->read() / 4;
  // state.label = "events";
  // uint cols = 128 / state.w;
  // uint rows = 128 / state.h;
  // for (uint yi = 0; yi < rows; yi++)
  // {
  //   for (uint xi = 0; xi < cols; xi++)
  //   {
  //     state.color = !screenBtns[xi % NUM_SCREEN_BTN]->read() ? ssd1351::RGB(255, 255, 255) : ssd1351::RGB(255, 0, 0);
  //     state.x = xi * state.w;
  //     state.y = yi * state.h;
  //     state.value += (sinf(xi * yi) * 0.5 + 0.5) * 10;
  //     UIComponents::drawParam(&display, state);
  //   }
  // }

  if (frontLeftButton->released())
  {
    delegate->frontLeftButtonClick();
  }

  if (frontRightButton->read() || !rightEncoderButton->read())
  {
    digitalWrite(FRONT_RIGHT_LED_PIN, true);
  }
  else
  {
    digitalWrite(FRONT_RIGHT_LED_PIN, false);
  }

  display.updateScreen();
}

UI *ui = new UI();