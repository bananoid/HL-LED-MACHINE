#include "Flower.h"
#include "AOYAMA_TREE/COMMON/Messages.h"
#include <WiFi.h>
#include "FastLED.h"

Flower *FlowerSingleton = new Flower();

void Flower::begin(int wifiChannel, ESPSortedBroadcast::PeerRecord *peerList, int nPeers, Scheduler *runner)
{
  // Peer
  ESPSortedBroadcast::Peer::begin(wifiChannel, peerList, nPeers);

  branchPeerId = peerDescription.id + NUMBER_OF_FLOWERS;

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
  FastLED.addLeds<WS2812B, 19, GRB>(leds, 24); // bottom
  ringLEDRenderer.begin(leds, 24);
  ringLEDSynth = new LEDSynth::LEDSynth(24, &ringLEDRenderer, runner);

  leds = new CRGB[1];
  FastLED.addLeds<WS2812B, 5, GRB>(leds, 1); // dot
  ballDotLEDRenderer.begin(leds, 1);
  ballDotLEDSynth = new LEDSynth::LEDSynth(1, &ballDotLEDRenderer, runner);
  ballDotLEDShaderSynth = ballDotLEDSynth->addLEDShaderSynth();

  layerALEDShaderSynth = ringLEDSynth->addLEDShaderSynth();
  layerBLEDShaderSynth = ringLEDSynth->addLEDShaderSynth();

  setSilentRingAnimation();
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
  // Serial.printf("peer id %i, branch id %i\n", peerDescription.id, branchPeerId);
}

void Flower::registerReceiveDataCB()
{
  esp_now_register_recv_cb([](const uint8_t *macaddr, const uint8_t *incomingData, int len) {
    FlowerSingleton->receiveDataCB(macaddr, incomingData, len);
  });
}

void Flower::receiveFilteredDataCB(uint8_t messageType, uint8_t sourceId, uint8_t targetId, const uint8_t *mac, const uint8_t *incomingData, int len)
{
  // Serial.printf("Received message  myId:%i to type:%i\n", peerDescription.id, messageType);

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
  // Serial.printf("Flower State Changed %i\n", state);

  this->state = state;

  switch (state)
  {
  case FlowerStates::SILENT:
  {
    Serial.println("Change State to SILENT");

    activation = 0;
    setSilentRingAnimation();
    break;
  }
  case FlowerStates::CALLING:
  {
    Serial.println("Change State to CALLING");

    setCallingRingAnimation();
    break;
  }
  case FlowerStates::ACTIVE:
  {
    Serial.println("Change State to ACTIVE");
    setActiveRingAnimation();

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
    setSilentRingAnimation();
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
    // send activation to the tree // and the branch
    FlowerActivationMessage msg;
    msg.activation = activation;
    broadcastMessage(&msg, sizeof(FlowerActivationMessage));

    float intensityActivation = constrain(activation * 5.0, 0.0, 1.0);

    layerALEDShaderSynth->targetState->globalIntensity = 1.0 - intensityActivation;
    layerBLEDShaderSynth->targetState->globalIntensity = intensityActivation;

    // Serial.printf("LA intensity %f  LB intensity %f \n", layerALEDShaderSynth->targetState->globalIntensity, layerBLEDShaderSynth->targetState->globalIntensity);
    // Serial.printf("activa %f  \n", activation);

    layerALEDShaderSynth->targetState->speed = -0.01 - activation * 1.0;
    layerBLEDShaderSynth->targetState->speed = 0.02 + activation * 2.0;
  }
}

void Flower::setSilentRingAnimation()
{

  // BLUE
  layerALEDShaderSynth->interpolationSpeed = 0.03;
  layerALEDShaderSynth->targetState->hueRad = 0.1;
  layerALEDShaderSynth->targetState->hue = 0.5;
  layerALEDShaderSynth->targetState->que = 1.3;
  layerALEDShaderSynth->targetState->sym = 0.9;
  layerALEDShaderSynth->targetState->speed = 0.1235;
  layerALEDShaderSynth->targetState->scale = 1.0;
  layerALEDShaderSynth->targetState->saturation = 1.0;

  // RED
  layerBLEDShaderSynth->interpolationSpeed = 0.03;
  layerBLEDShaderSynth->targetState->hueRad = 0.03;
  layerBLEDShaderSynth->targetState->hue = 0.0;
  layerBLEDShaderSynth->targetState->que = 1.3;
  layerBLEDShaderSynth->targetState->sym = 0.9;
  layerBLEDShaderSynth->targetState->speed = -0.213;
  layerBLEDShaderSynth->targetState->scale = 1.0;
  layerBLEDShaderSynth->targetState->saturation = 1.0;

  layerALEDShaderSynth->targetState->fmAmo = 4.0;
  layerBLEDShaderSynth->targetState->fmAmo = 4.0;

  layerALEDShaderSynth->targetState->globalIntensity = 0;
  layerBLEDShaderSynth->targetState->globalIntensity = 0;
}

void Flower::setCallingRingAnimation()
{
  layerALEDShaderSynth->targetState->fmAmo = 20.0;
  layerBLEDShaderSynth->targetState->fmAmo = 20.0;

  layerALEDShaderSynth->targetState->scale = 3.0;
  layerBLEDShaderSynth->targetState->scale = 3.0;
}
void Flower::setActiveRingAnimation()
{
  // layerALEDShaderSynth->targetState->hue = 0.5;
  // layerBLEDShaderSynth->targetState->hue = 0.0;

  // layerALEDShaderSynth->targetState->fmAmo = 4.0;
  // layerBLEDShaderSynth->targetState->fmAmo = 4.0;

  // layerALEDShaderSynth->targetState->scale = 1.0;
  // layerBLEDShaderSynth->targetState->scale = 1.0;

  // layerALEDShaderSynth->targetState->intensity = 1.0;
  // layerBLEDShaderSynth->targetState->intensity = 1.0;
}