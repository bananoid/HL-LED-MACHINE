#include "MusicMachine.h"

#include "AOYAMA_TREE/COMMON/Messages.h"
#include "AOYAMA_TREE/COMMON/TrackerFactory.h"

using namespace HLMusicMachine;

MusicMachine::MusicMachine(Scheduler *runner)
{
  this->runner = runner;
  tracker = new Tracker(runner);
  TrackerFactory::buildSong(tracker);
  tracker->clock->play();

  //Start Stop button
  startStopButton.attach(9, INPUT_PULLUP); // USE EXTERNAL PULL-UP
  startStopButton.interval(5);
  startStopButton.setPressedState(LOW);

  // Serial Messenger
  Serial.begin(BAUD_RATE);
  Serial6.begin(BAUD_RATE);
  SerialMessengerSingleton->delegate = this;
  SerialMessengerSingleton->begin(&Serial6, BAUD_RATE);

  //Test Message
  benchmarkTask.set(200 * TASK_MILLISECOND, TASK_FOREVER, [this]() {
    BenchmarkMessage msg;
    msg.time = micros();
    Serial.printf("T Benchmark time %i\n", msg.time);
    SerialMessengerSingleton->sendMessage(&msg, sizeof(BenchmarkMessage));
  });
  runner->addTask(benchmarkTask);
  benchmarkTask.disable(); // Enable for benchmarck
}

void MusicMachine::update()
{
  // button
  startStopButton.update();
  if (startStopButton.pressed())
  {
    tracker->clock->playStop();
    Serial.println("button press");
  }

  // serial messenger
  SerialMessengerSingleton->update();
}

void MusicMachine::serialMessengerReceiveData(const uint8_t *incomingData, int len)
{
  uint8_t messageType = SerialMessengerSingleton->getMessageTypeFromData(incomingData);

  switch (messageType)
  {

  case PING:
  {
    Serial.println("PING");
    break;
  }
  case BENCHMARK_MESSAGE:
  {
    BenchmarkMessage msg;
    memcpy(&msg, incomingData, sizeof(BenchmarkMessage));
    unsigned long deltaTime = micros() - msg.time;
    Serial.printf("R Benchmark time %i %i\n", msg.time, deltaTime);
    break;
  }
  default:
    break;
  }
}