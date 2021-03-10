#include "Clock.h"
#include <Arduino.h>

namespace HLSequencer
{
  Clock::Clock(Scheduler *runner) : Task(1 * TASK_SECOND, TASK_FOREVER, runner, false)
  {
  }

  bool Clock::Callback()
  {

#ifdef MIDI_INTERFACE
    if (tickCounter == 0)
    {
      usbMIDI.sendRealTime(usbMIDI.Start);
    }
    usbMIDI.sendRealTime(usbMIDI.Clock);
#endif

    setInterval(clockInterval);
    delegate->clockTick();
    tickCounter++;
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
  };

  void Clock::stop()
  {
    isPlaying = false;
    Serial.println("Stop");

    disable();
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