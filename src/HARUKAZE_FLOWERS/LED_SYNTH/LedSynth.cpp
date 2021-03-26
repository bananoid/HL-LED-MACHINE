#include "LedSynth.h"
#include <Arduino.h>

void LedSynth::begin(Scheduler *runner)
{
  //Start Stop button
  startStopButton.attach(9, INPUT_PULLUP); // USE EXTERNAL PULL-UP
  startStopButton.interval(5);
  startStopButton.setPressedState(LOW);

  // Serial Messenger
  Serial.begin(BAUD_RATE);
  Serial6.begin(BAUD_RATE);
  SerialMessengerSingleton->delegate = this;
  SerialMessengerSingleton->begin(&Serial6, BAUD_RATE);

  // MIDI
  MIDIUSBHostSingleton->begin(this);

  // // Ping
  // ping.set(TASK_SECOND, TASK_FOREVER, [this]() {
  //   BaseMessage msg;
  //   msg.sourceId = 0;
  //   msg.targetId = 2;
  //   SerialMessengerSingleton->sendData((uint8_t *)&msg, sizeof(BaseMessage));
  //   Serial.println("S:" + String(msg.sourceId) + "->" + String(msg.targetId) + "[PING]");
  //   // screen->println("S:" + String(msg.sourceId) + "->" + String(msg.targetId) + "[PING] " + String(random(99)), 3);
  // });
  // runner->addTask(ping);
  // ping.enable();

  // Screen
  screen = new OledScreen(8, 22);
  screen->begin();
  screen->println("Hidden Layer", 0);
  displayScreen.set(50 * TASK_MILLISECOND, TASK_FOREVER, [this]() {
    screen->displayScreen();
  });
  runner->addTask(displayScreen);
  displayScreen.enable();

  //Audio Analyzer
  AudioAnalyzerSingleton->begin(this);

  broadcastBands.set(16 * TASK_MILLISECOND, TASK_FOREVER, [this]() {
    AudioAnalyzerSingleton->update();
  });
  runner->addTask(broadcastBands);
  broadcastBands.enable();

  // LED LAYERS
  for (int i = 0; i < N_LAYERS; i++)
  {
    /* code */
    ledSynthLayerMessages[i] = new LedSynthLayerMessage();
  }

  ledSynthGlobalMessage = new LedSynthGlobalMessage();
}

void LedSynth::update()
{
  // button
  startStopButton.update();
  if (startStopButton.pressed())
  {
    Serial.println("button press");
  }

  // Serial messenger
  SerialMessengerSingleton->update();

  // MIDI
  MIDIUSBHostSingleton->update();
}

void LedSynth::serialMessengerReceiveMsg(BaseMessage *message){
    // Serial.println("Receive a message!");
    // screen->println("Receive a message!", 4);
};

void LedSynth::serialMessengerReceiveData(const uint8_t *incomingData, int len)
{
  Serial.println("Receive data! ");
  screen->println("Receive data! " + String(random(99)), 5);
};

void LedSynth::audioAnalyzerOnBandsUpdate(float bandLowVal, float bandMidVal, float bandHighVal)
{
  char c[22];
  sprintf(c, "L:%3d M:%3d H:%3d", int(bandLowVal * 999), int(bandMidVal * 999), int(bandHighVal * 999));
  screen->println(c, 2);

  AudioBandsMessage msg;
  msg.sourceId = 1;
  msg.targetId = 0; // 0 to bradcast
  msg.bandLowVal = bandLowVal;
  msg.bandMidVal = bandMidVal;
  msg.bandHighVal = bandHighVal;

  SerialMessengerSingleton->sendData((uint8_t *)&msg, sizeof(AudioBandsMessage));
  Serial.println("S:" + String(msg.sourceId) + "->" + String(msg.targetId) + "[AudioBand]");
  screen->println("Sending data [" + String(msg.type) + "]", 4);
}

void LedSynth::MIDIUSBHostOnReceiveData(uint8_t channel, uint8_t type, uint8_t data1, uint8_t data2)
{
  char c[22];
  sprintf(c, "T%3i D%3i D%3i C%3i", type, data1, data2, channel);
  screen->println(c, 3);

  // changing layer parameters
  if (channel == 2)
  {
    bool globalChanged = false;
    bool layer1Changed = false;
    bool layer2Changed = false;

    // layer 1
    if (data1 == 13)
    {
      ledSynthLayerMessages[0]->que = map((float)data2, 0.f, 127.f, 0.f, 3.6f);
      layer1Changed = true;
    }
    else if (data1 == 29) // c1 r2
    {
      ledSynthLayerMessages[0]->sym = map((float)data2, 0.f, 127.f, 0.f, 1.f);
      layer1Changed = true;
    }
    else if (data1 == 49) // c1 r3
    {
      ledSynthLayerMessages[0]->fmAmo = map((float)data2, 0.f, 127.f, 0.1f, 8.f);
      layer1Changed = true;
    }
    else if (data1 == 77) // c1 r4
    {
      ledSynthLayerMessages[0]->fmFrq = map((float)data2, 0.f, 127.f, 0.f, 5.f);
      layer1Changed = true;
    }
    else if (data1 == 14) // c2 r1
    {
      ledSynthLayerMessages[0]->hue = map((float)data2, 0.f, 127.f, 0.f, 1.0f);
      layer1Changed = true;
    }
    else if (data1 == 30) // c2 r2
    {
      ledSynthLayerMessages[0]->hueRad = map((float)data2, 0.f, 127.f, 0.f, 0.5f);
      layer1Changed = true;
    }
    else if (data1 == 50) // c2 r3
    {
      ledSynthLayerMessages[0]->speed = map((float)data2, 0.f, 127.f, -LAYER_MAX_SPEED, LAYER_MAX_SPEED);
      layer1Changed = true;
    }
    else if (data1 == 78) // c2 r4
    {
      ledSynthLayerMessages[0]->scale = map((float)data2, 0.f, 127.f, MIN_SCALE, MAX_SCALE);
      layer1Changed = true;
    }
    else if (data1 == 15) // c2 r2
    {
      ledSynthLayerMessages[0]->audioInfluenceHighBand = map((float)data2, 0.f, 127.f, 0.f, 1.f);
      layer1Changed = true;
    }
    else if (data1 == 31) // c2 r3
    {
      ledSynthLayerMessages[0]->audioInfluenceMidBand = map((float)data2, 0.f, 127.f, 0.f, 1.f);
      layer1Changed = true;
    }
    else if (data1 == 51) // c2 r4
    {
      ledSynthLayerMessages[0]->audioInfluenceLowBand = map((float)data2, 0.f, 127.f, 0.f, 1.f);
      layer1Changed = true;
    }
    else if (data1 == 79) // c2 r4
    {
      ledSynthLayerMessages[0]->intensity = map((float)data2, 0.f, 127.f, 0.f, 1.f);
      layer1Changed = true;
    }

    // Layer 2
    else if (data1 == 16) // c4 r1
    {
      ledSynthLayerMessages[1]->que = map((float)data2, 0.f, 127.f, 0.f, 3.6f);
      layer2Changed = true;
    }
    else if (data1 == 32) // c4 r2
    {
      ledSynthLayerMessages[1]->sym = map((float)data2, 0.f, 127.f, 0.f, 1.f);
      layer2Changed = true;
    }
    else if (data1 == 52) // c4 r3
    {
      ledSynthLayerMessages[1]->fmAmo = map((float)data2, 0.f, 127.f, 0.1f, 8.f);
      layer2Changed = true;
    }
    else if (data1 == 80) // c4 r4
    {
      ledSynthLayerMessages[1]->fmFrq = map((float)data2, 0.f, 127.f, 0.f, 5.f);
      layer2Changed = true;
    }
    else if (data1 == 17) // c5 r1
    {
      ledSynthLayerMessages[1]->hue = map((float)data2, 0.f, 127.f, 0.f, 1.0f);
      layer2Changed = true;
    }
    else if (data1 == 33) // c5 r2
    {
      ledSynthLayerMessages[1]->hueRad = map((float)data2, 0.f, 127.f, 0.f, 0.5f);
      layer2Changed = true;
    }
    else if (data1 == 53) // c5 r3
    {
      ledSynthLayerMessages[1]->speed = map((float)data2, 0.f, 127.f, -LAYER_MAX_SPEED, LAYER_MAX_SPEED);
      layer2Changed = true;
    }
    else if (data1 == 81) // c5 r4
    {
      ledSynthLayerMessages[1]->scale = map((float)data2, 0.f, 127.f, MIN_SCALE, MAX_SCALE);
      layer2Changed = true;
    }
    else if (data1 == 18) // c6 r1
    {
      ledSynthLayerMessages[1]->audioInfluenceHighBand = map((float)data2, 0.f, 127.f, 0.f, 1.f);
      layer2Changed = true;
    }
    else if (data1 == 34) // c6 r2
    {
      ledSynthLayerMessages[1]->audioInfluenceMidBand = map((float)data2, 0.f, 127.f, 0.f, 1.f);
      layer2Changed = true;
    }
    else if (data1 == 54) // c6 r3
    {
      ledSynthLayerMessages[1]->audioInfluenceLowBand = map((float)data2, 0.f, 127.f, 0.f, 1.f);
      layer2Changed = true;
    }
    else if (data1 == 82) // c6 r4
    {
      ledSynthLayerMessages[1]->intensity = map((float)data2, 0.f, 127.f, 0.f, 1.f);
      layer2Changed = true;
    }

    // GLOBAL
    else if (data1 == 19) // c7 r1
    {
      ledSynthGlobalMessage->saturation = map((float)data2, 0.f, 127.f, 0.f, 1.f);
      globalChanged = true;
    }
    else if (data1 == 83) // c7 r4
    {
      ledSynthGlobalMessage->interpolationSpeed = map((float)data2, 0.f, 127.f, 0.f, 1.f);
      globalChanged = true;
    }
    else if (data1 == 84) // c8 r4
    {
      ledSynthGlobalMessage->audioFilterSpeed = map((float)data2, 0.f, 127.f, 0.f, 1.f);
      globalChanged = true;
    }

    if (globalChanged)
    {
      SerialMessengerSingleton->sendData((uint8_t *)ledSynthGlobalMessage, sizeof(LedSynthGlobalMessage));
    }
    else if (layer1Changed)
    {
      SerialMessengerSingleton->sendData((uint8_t *)ledSynthLayerMessages[0], sizeof(LedSynthLayerMessage));
    }
    else if (layer2Changed)
    {
      SerialMessengerSingleton->sendData((uint8_t *)ledSynthLayerMessages[1], sizeof(LedSynthLayerMessage));
    }
  }

  // independent address
  if (channel == 3)
  {

    // float intensity;
    bool intensityChanged = false;
    uint8_t peerId;

    if (data1 == 77) // c1 r4
    {
      peerId = 2;
      intensityChanged = true;
    }
    else if (data1 == 78) // c2 r4
    {
      peerId = 3;
      intensityChanged = true;
    }
    else if (data1 == 79) // c3 r4
    {
      peerId = 4;
      intensityChanged = true;
    }
    else if (data1 == 80) // c4 r4
    {
      peerId = 5;
      intensityChanged = true;
    }
    else if (data1 == 81) // c5 r4
    {
      peerId = 6;
      intensityChanged = true;
    }
    else if (data1 == 82) // c6 r4
    {
      peerId = 7;
      intensityChanged = true;
    }
    else if (data1 == 83) // c7 r4
    {
      peerId = 8;
      intensityChanged = true;
    }
    else if (data1 == 84) // c8 r4
    {
      peerId = 2;
      intensityChanged = true;
    }

    if (intensityChanged)
    {
      /* code */
      ledSynthGlobalMessage->globalIntensity = map((float)data2, 0.f, 127.f, 0.f, 3.6f);
      ledSynthGlobalMessage->targetId = peerId;

      SerialMessengerSingleton->sendData((uint8_t *)ledSynthGlobalMessage, sizeof(LedSynthGlobalMessage));
    }
  }
}
