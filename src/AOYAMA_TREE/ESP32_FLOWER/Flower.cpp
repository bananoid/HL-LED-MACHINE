#include "Flower.h"
#include "AOYAMA_TREE/COMMON/Messages.h"
#include <WiFi.h>
#include "FastLED.h"

Flower *FlowerSingleton = new Flower();

void Flower::begin(int wifiChannel, ESPSortedBroadcast::PeerRecord *peerList, int nPeers, Scheduler *runner)
{
  // Peer
  ESPSortedBroadcast::Peer::begin(wifiChannel, peerList, nPeers);

#ifndef OLEDSCREEN_DISABLED
  // Screen
  screen = new OledScreen(8, 22);
  screen->begin();
  screen->println(FlowerSingleton->peerDescription.name, 0);
  screen->println(WiFi.macAddress(), 1);
  screen->displayScreen();
  displayScreen.set(50 * TASK_MILLISECOND, TASK_FOREVER, [this]() {
    screen->sayHello(2);
    screen->displayScreen();
  });
  runner->addTask(displayScreen);
  displayScreen.enable();
#endif

  // Flower State
  activationUpdateTask.set(16 * TASK_MILLISECOND, TASK_FOREVER, [this]() {
    updateActivation();
  });
  runner->addTask(activationUpdateTask);
  activationUpdateTask.enable();

  // LED
  CRGB *leds;

  leds = new CRGB[24];
  FastLED.addLeds<WS2812B, 18, GRB>(leds, 24); // top
  topRingLEDRenderer.begin(leds, 24);
  topRingLEDSynth = new LEDSynth::LEDSynth(24, &topRingLEDRenderer, runner);
  topRingLEDShaderSynth = topRingLEDSynth->addLEDShaderSynth();

  leds = new CRGB[24];
  FastLED.addLeds<WS2812B, 19, GRB>(leds, 24); // bottom
  bottomRingLEDRenderer.begin(leds, 24);
  bottomRingLEDSynth = new LEDSynth::LEDSynth(24, &bottomRingLEDRenderer, runner);
  bottomRingLEDShaderSynth = bottomRingLEDSynth->addLEDShaderSynth();
  bottomRingLEDShaderSynth->interpolationSpeed = 1;
  bottomRingLEDShaderSynth->targetState->hueRad = 0.0;
  bottomRingLEDShaderSynth->targetState->hue = 0.0;
  bottomRingLEDShaderSynth->targetState->que = 0.0;
  bottomRingLEDShaderSynth->targetState->sym = 0;
  bottomRingLEDShaderSynth->targetState->speed = 10.0;
  bottomRingLEDShaderSynth->targetState->scale = 1.0;
  bottomRingLEDShaderSynth->targetState->globalIntensity = 0.0;
  bottomRingLEDShaderSynth->targetState->saturation = 0.0;

  leds = new CRGB[1];
  FastLED.addLeds<WS2812B, 5, GRB>(leds, 1); // dot
  ballDotLEDRenderer.begin(leds, 1);
  ballDotLEDSynth = new LEDSynth::LEDSynth(1, &ballDotLEDRenderer, runner);
  ballDotLEDShaderSynth = ballDotLEDSynth->addLEDShaderSynth();

  // IMU
  // imu = new IMUSensor(this);
  // imu->begin();
  // readIMU.set(10 * TASK_MILLISECOND, TASK_FOREVER, [this]() {
  //   imu->update();
  // });
  // runner->addTask(readIMU);
  // readIMU.enable();

  // touchSensor
  touchSensor = new TouchSensor(this);
  touchSensorUpdateTask.set(1 * TASK_MILLISECOND, TASK_FOREVER, [this]() {
    touchSensor->update();
  });
  runner->addTask(touchSensorUpdateTask);
  touchSensorUpdateTask.enable();
}

void Flower::update()
{
}

void Flower::registerReceiveDataCB()
{
  esp_now_register_recv_cb([](const uint8_t *macaddr, const uint8_t *incomingData, int len) {
    FlowerSingleton->receiveDataCB(macaddr, incomingData, len);
  });
}

void Flower::receiveFilteredDataCB(uint8_t messageType, uint8_t sourceId, uint8_t targetId, const uint8_t *mac, const uint8_t *incomingData, int len)
{
  Serial.printf("Received message from %i to %i\n", sourceId, targetId);

  if (targetId == peerDescription.id)
  {
    /* code */ switch (messageType)
    {
    case FLOWER_STATE:
    {
      FlowerStateMessage msg;
      memcpy(&msg, incomingData, sizeof(FlowerStateMessage));
      flowerStateChanged((FlowerStates)msg.state);
      break;
    }
    case FLOWER_ACTIVATION_PARAMETERS:
    {
      FlowerActivationParametersMessage msg;
      memcpy(&msg, incomingData, sizeof(FlowerActivationParametersMessage));
      activationIncrease = msg.activationIncrease;
      activationDecay = msg.activationDecay;
      break;
    }

    default:
      break;
    }
  }
}

void Flower::flowerStateChanged(FlowerStates state)
{
  Serial.printf("Flower State Changed %i\n", state);

  this->state = state;

  switch (state)
  {
  case FlowerStates::SILENT:
  {
    Serial.println("Change State to SILENT");
    bottomRingLEDShaderSynth->targetState->hue = 0;
    bottomRingLEDShaderSynth->targetState->globalIntensity = 0.0;
    bottomRingLEDShaderSynth->targetState->saturation = 0;

    activation = 0;
    break;
  }
  case FlowerStates::CALLING:
  {
    Serial.println("Change State to CALLING");
    bottomRingLEDShaderSynth->targetState->globalIntensity = 0.3;
    bottomRingLEDShaderSynth->targetState->saturation = 0;
    break;
  }
  case FlowerStates::ACTIVE:
  {
    Serial.println("Change State to ACTIVE");
    bottomRingLEDShaderSynth->targetState->hue = 0.5;
    bottomRingLEDShaderSynth->targetState->globalIntensity = 1.;
    bottomRingLEDShaderSynth->targetState->saturation = 1;

    break;
  }
  }
}

void Flower::onIMUOrientationData(sensors_event_t *orientationData)
{
  double x, y, z;
  x = orientationData->orientation.x;
  y = orientationData->orientation.y;
  z = orientationData->orientation.z;
}

void Flower::touchSensorOnTouch(int touchId) {}

void Flower::updateActivation()
{
  if (state == SILENT)
  {
    activation = 0;
    return;
  }
  else
  {

    activation -= activationDecay;
    activation = max(activation, 0.0f);

    int nTouches = touchSensor->getCrownOnTouches();
    if (nTouches > 0)
    {
      activation += activationIncrease;
      activation = min(activation, 1.0f);
    }
  }

  FlowerActivationMessage msg;
  msg.activation = activation;
  broadcastMessage(&msg, sizeof(FlowerActivationMessage));
}