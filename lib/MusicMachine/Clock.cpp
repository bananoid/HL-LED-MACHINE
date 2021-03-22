#include "Clock.h"
#include <Arduino.h>

namespace HLMusicMachine
{
  Clock::Clock(Scheduler *runner) : Task(1 * TASK_SECOND, TASK_FOREVER, runner, false)
  {
    pinMode(13, OUTPUT);
  }

  bool Clock::Callback()
  {
    if (tickCounter % (24) == 0)
    {
      digitalWrite(13, true);
    }
    else if ((tickCounter + 12) % (24) == 0)
    {
      digitalWrite(13, false);
    }

#ifdef MIDI_INTERFACE
    usbMIDI.sendRealTime(usbMIDI.Clock);
#endif

    setInterval(clockInterval);
    delegate->clockTick();
    tickCounter++;

    return true;
  }

  void Clock::setBpm(float bpm)
  {
    bpm = constrain(bpm, minBpm, maxBpm);

    this->bpm = bpm;
    this->clockInterval = 60 * TASK_SECOND / bpm / this->clockDivider; // microseconds

    Serial.printf("Bpm is  %f\n", bpm);
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
    setInterval(clockInterval);
    enable();

#ifdef MIDI_INTERFACE
    usbMIDI.sendRealTime(usbMIDI.Start);
#endif
  };

  void Clock::stop()
  {
    isPlaying = false;
    Serial.println("Stop");

    disable();

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
}