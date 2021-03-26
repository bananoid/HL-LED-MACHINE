#include "LedSynth.h"
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

  // Ping
  ping.set(TASK_SECOND, TASK_FOREVER, [this]() {
    BaseMessage msg;
    msg.sourceId = 0;
    msg.targetId = 2;
    SerialMessengerSingleton->sendData((uint8_t *)&msg, sizeof(BaseMessage));
    Serial.println("S:" + String(msg.sourceId) + "->" + String(msg.targetId) + "[PING]");
    // screen->println("S:" + String(msg.sourceId) + "->" + String(msg.targetId) + "[PING] " + String(random(99)), 3);
  });
  runner->addTask(ping);
  ping.enable();

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

  // Audio analyzer
  AudioAnalyzerSingleton->update();
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
}
