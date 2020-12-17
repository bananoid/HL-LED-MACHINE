#include "MainController.h"

MainController::MainController()
{
  midiControl = new MIDIControl();
  midiControl->delegate = this;
}
void MainController::begin()
{
  midiControl->begin();
}
void MainController::update()
{
  midiControl->update();
}

void MainController::midiControlReceiveMsg(ControlMsg *message)
{
  Serial.printf("Receive Message type :: %i - channel :: %i - id :: %i", message->type, message->channel, message->id);
  if (message->type == LEDSynthMessages::CONTROL_VALUE_MSG)
  {
    ControlValue cMsg;
    memcpy(&cMsg, message, sizeof(cMsg));

    Serial.printf(" - Value :: %f", cMsg.value);
  }
  else if (message->type == LEDSynthMessages::CONTROL_BUTTON_PRESS_MSG)
  {
    Serial.printf(" - Button press");
  }
  else if (message->type == LEDSynthMessages::CONTROL_BUTTON_RELEASE_MSG)
  {
    Serial.printf(" - Button release");
  }
  Serial.println();
}