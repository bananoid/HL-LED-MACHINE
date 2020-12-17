#include "MainController.h"
#include <Arduino.h>

MainController::MainController()
{
  pinMode(13, OUTPUT);

  midiControl = new MIDIControl();
  midiControl->delegate = this;

  audioControl = new HLAudioControl::AudioControl();
  audioControl->delegate = this;
}
void MainController::begin()
{
  midiControl->begin();
  audioControl->begin();
}
void MainController::update()
{
  midiControl->update();
  audioControl->update();
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

void MainController::audioControlReceiveMsg(AudioSignalsMsg *message)
{
  // Serial.println(message->lowBand);
  analogWrite(13, message->lowBand * 255);
}