#include "Clock.h"
#include <Arduino.h>

#include "SerialMIDI.h"

namespace HLMusicMachine
{

  Clock::Clock(Scheduler *runner)
  {

    pinMode(clockLedPort, OUTPUT);

    clockTask.set(TASK_SECOND, TASK_FOREVER, [this]()
                  {
                    unsigned long curTime = micros();
                    tick();
                    debugTickTime = micros() - curTime;
                  });
    runner->addTask(clockTask);
    clockTask.disable();
  }

  void Clock::tick()
  {

    // if (tickCounter == clockDivider * 2) // Preroll Start
    if (tickCounter == 0) // Preroll Start
    {
      serialMIDI.clockStart();
#ifdef MIDI_INTERFACE
      // usbMIDI.sendRealTime(usbMIDI.Start);
#endif
    }

    if (tickCounter % (24) == 0)
    {
      digitalWrite(clockLedPort, true);

      if (externalClock)
      {
        // TODO: Calculate clockInterval from external clock
        // int deltaTime;
        // unsigned long curTime = micros();
        // deltaTime = curTime - prevClickTime;
        // prevClickTime = curTime;
        // Serial.printf("clockTick time %i \n", deltaTime);
      }
    }
    else if ((tickCounter + 12) % (24) == 0)
    {
      digitalWrite(clockLedPort, false);
      Serial.println(debugTickTime);
    }

#ifdef MIDI_INTERFACE
    // usbMIDI.sendRealTime(usbMIDI.Clock);
#endif

    clockTask.setInterval(clockInterval);
    delegate->clockTick();
    tickCounter++;

    if (tickCounter % (12) == 0)
    {
      serialMIDI.sendTestNotes(true);
    }
    else if ((tickCounter + 6) % (12) == 0)
    {
      serialMIDI.sendTestNotes(false);
    }

    serialMIDI.clockTick();
  }

  void Clock::setBpm(float bpm)
  {
    bpm = constrain(bpm, minBpm, maxBpm);

    this->bpm = bpm;
    clockInterval = (float)(60 * TASK_SECOND) / bpm / (float)clockDivider; // microseconds

    Serial.printf("Bpm is  %f %i\n", bpm, clockInterval);
  }

  float Clock::getBpm()
  {
    return bpm;
  }

  void Clock::play()
  {
    isPlaying = true;
    // Serial.println("Play");

    tickCounter = clockDivider * -2; // preroll 2 brats
    if (!externalClock)
    {
      setBpm(bpm);
      clockTask.setInterval(clockInterval);
      clockTask.enable();
    }
  };

  void Clock::stop()
  {
    isPlaying = false;
    // Serial.println("Stop");

    if (!externalClock)
    {
      clockTask.disable();
    }

    serialMIDI.clockStop();
#ifdef MIDI_INTERFACE
    // usbMIDI.sendRealTime(usbMIDI.Stop);
#endif
  };

  void Clock::playStop()
  {
    if (isPlaying)
    {
      stop();
    }
    else
    {
      play();
    }
  };

  float Clock::getBpmPercentage()
  {
    return map(getBpm(), minBpm, maxBpm, 0.0, 1.0);
  }

  void Clock::increaseBpm(int increase)
  {
    float bpm = getBpm() + increase;
    setBpm(bpm);
  }

  void Clock::syncTo(unsigned long syncTickCounter, float bpm)
  {
    tickCounter = syncTickCounter;
    setBpm(bpm);

    // long deltaTicks = tickCounter - syncTickCounter;
    // Serial.printf("deltaTicks:%i tickCounter:%i syncTickCounter:%i\n", deltaTicks, tickCounter, syncTickCounter);
  }

}
