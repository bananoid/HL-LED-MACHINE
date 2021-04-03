#include "Clock.h"
#include <Arduino.h>

namespace HLMusicMachine
{
  Clock::Clock(Scheduler *runner)
  {
    pinMode(31, OUTPUT);

    clockTask.set(TASK_SECOND, TASK_FOREVER, [this]() {
      if (tickCounter % (24) == 0)
      {
        digitalWrite(31, true);
      }
      else if ((tickCounter + 12) % (24) == 0)
      {
        digitalWrite(31, false);
      }

#ifdef MIDI_INTERFACE
      usbMIDI.sendRealTime(usbMIDI.Clock);
#endif

      clockTask.setInterval(clockInterval);
      delegate->clockTick();
      tickCounter++;
    });
    runner->addTask(clockTask);
    clockTask.disable();
  }

  void Clock::setBpm(float bpm)
  {
    bpm = constrain(bpm, minBpm, maxBpm);

    this->bpm = bpm;
    this->clockInterval = 60 * TASK_SECOND / bpm / this->clockDivider; // microseconds

    // Serial.printf("Bpm is  %f\n", bpm);
  }

  float Clock::getBpm()
  {
    return bpm;
  }

  void Clock::play()
  {
    isPlaying = true;
    Serial.println("Play");

    tickCounter = 0;
    setBpm(bpm);
    clockTask.setInterval(clockInterval);
    clockTask.enable();

#ifdef MIDI_INTERFACE
    usbMIDI.sendRealTime(usbMIDI.Start);
#endif
  };

  void Clock::stop()
  {
    isPlaying = false;
    Serial.println("Stop");

    clockTask.disable();

#ifdef MIDI_INTERFACE
    usbMIDI.sendRealTime(usbMIDI.Stop);
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