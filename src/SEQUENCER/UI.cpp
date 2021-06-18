#include "UI.h"

#include <Arduino.h>
#include <SPI.h>
#include <ssd1351.h>
#include "GFX_fonts/Font5x7FixedMono.h"

//typedef ssd1351::IndexedColor Color;
// typedef ssd1351::LowColor Color;
typedef ssd1351::HighColor Color;

// auto display = ssd1351::SSD1351<Color, ssd1351::NoBuffer, 128, 96>();
auto display = ssd1351::SSD1351<Color, ssd1351::SingleBuffer, 128, 128>();
// auto display = ssd1351::SSD1351<Color, ssd1351::DoubleBuffer, 128, 128>();

void UI::begin(Scheduler *runner)
{
  display.begin();

  leftEncoder = new Encoder(ENCODER_LEFT_PIN_A, ENCODER_LEFT_PIN_B);
  rightEncoder = new Encoder(ENCODER_RIGHT_PIN_A, ENCODER_RIGHT_PIN_B);

  oledTask.set(TASK_MILLISECOND * 16, TASK_FOREVER, [this]()
               { ui->updateOled(); });
  runner->addTask(oledTask);
  oledTask.enable();

  encoderTask.set(TASK_MILLISECOND * 16, TASK_FOREVER, [this]()
                  { ui->updateEncoders(); });
  runner->addTask(encoderTask);
  encoderTask.enable();

  leftEncoderButton = new Bounce();
  leftEncoderButton->attach(ENCODER_LEFT_PIN_SW, INPUT);
  leftEncoderButton->interval(25);

  rightEncoderButton = new Bounce();
  rightEncoderButton->attach(ENCODER_RIGHT_PIN_SW, INPUT);
  rightEncoderButton->interval(25);
}

void UI::updateOled()
{
  float t = micros() / 300000.0;

  display.fillScreen(ssd1351::RGB(255, 200, 200));

  float leftNipplesMult = leftEncoderButton->read() ? 1.5 : 1;
  float rightNipplesMult = rightEncoderButton->read() ? 1.5 : 1;

  float lNx = leftEncoder->read() * 0.1;
  float rNx = rightEncoder->read() * 0.1;

  display.fillCircle(10 + lNx, 50, 16 * leftNipplesMult, ssd1351::RGB(255, 120, 100));
  display.fillCircle(10 + lNx, 50, 7 * leftNipplesMult, ssd1351::RGB(255, 80, 70));
  display.fillCircle(128 - 10 + rNx, 50, 16 * rightNipplesMult, ssd1351::RGB(255, 120, 100));
  display.fillCircle(128 - 10 + rNx, 50, 7 * rightNipplesMult, ssd1351::RGB(255, 80, 70));

  for (int x = 0; x < 128; x++)
  {
    float fm = sinf(x * 0.01524 + t * 0.1235 + lNx) * 10;

    float s = sinf(x * 0.005 * fm + t + rNx);
    s = asinf(s) / HALF_PI * 0.2 + 0.5;

    display.drawLine(x, 128, x, (s)*128, ssd1351::RGB(255, 180, 180));
    // display.drawPixel(x, (s)*128 + 20, ssd1351::RGB(255, 0, 0));
  }

  // display.drawRoundRect(10, 10, 128 - 20, 128 - 20, 20, ssd1351::RGB(0, 100, 255));

  display.setFont(Font5x7FixedMono);
  display.setTextSize(1);
  display.setCursor(20, 100);
  display.setTextColor(ssd1351::RGB(30, 30, 30));
  display.print(rightEncoder->read());
  display.setCursor(20, 120);
  display.setTextColor(ssd1351::RGB(30, 30, 30));
  display.setTextSize(2);
  display.print(leftEncoder->read());

  display.updateScreen();
}

void UI::updateEncoders()
{
  leftEncoderButton->update();
  rightEncoderButton->update();
}

UI *ui = new UI();