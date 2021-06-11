#include "Clock.h"
#include <Arduino.h>

#include "SerialMIDI.h"

namespace HLMusicMachine
{

  Clock::Clock()
  {
  }

  void Clock::begin()
  {
    pinMode(clockLedPort, OUTPUT);
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

    serialMIDI.clockTick();

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
      // Serial.println(debugTickTime);
    }

#ifdef MIDI_INTERFACE
    // usbMIDI.sendRealTime(usbMIDI.Clock);
#endif

    timer.update(clockInterval);

    delegate->clockTick();
    tickCounter++;

    // if (tickCounter % (12) == 0)
    // {
    //   serialMIDI.sendTestNotes(true);
    // }
    // else if ((tickCounter + 6) % (12) == 0)
    // {
    //   serialMIDI.sendTestNotes(false);
    // }
  }

  void Clock::setBpm(float bpm)
  {
    bpm = constrain(bpm, minBpm, maxBpm);

    this->bpm = bpm;
    clockInterval = 60000000.0f / bpm / (float)clockDivider; // microseconds

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
      timer.begin(timerTick, clockInterval);
    }
  };

  void Clock::stop()
  {
    isPlaying = false;
    // Serial.println("Stop");

    if (!externalClock)
    {
      timer.end();
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

  Clock *masterClock = new Clock();

  void timerTick()
  {
    // unsigned long curTime = micros();
    masterClock->tick();
    // masterClock->debugTickTime = micros() - curTime;
  }

}
