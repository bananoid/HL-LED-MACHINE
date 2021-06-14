#pragma once

#include <Arduino.h>

#include <MIDI.h>

namespace HLMusicMachine
{
  static void timerTick();
  // Delegation: this is to allow clock tick to be called by main controller
  class ClockDelegate
  {
  public:
    virtual void clockTick(); // virtual because it is not implemented in the class
  };
  class Clock
  {
  private:
    /* data */

  public:
    Clock();

    void begin();

    IntervalTimer timer;

    bool externalClock = false;
    void tick();

    ClockDelegate *delegate;

    // const int clockLedPort = 13; //31
    const int clockLedPort = 31; //31
    void clockTick();
    unsigned long tickCounter = 0;
    unsigned long prevClickTime = 0;

    // BPM
    float getBpm();
    void setBpm(float bpm);

    float bpm = 100;
    const int clockDivider = 24;           // number of time intervals within a beat
    unsigned long clockInterval = 1000000; // default value to 1 sec
    const float minBpm = 30;
    const float maxBpm = 300;

    bool isPlaying = false;
    void play();
    void stop();
    void playStop();

    float getBpmPercentage();
    void increaseBpm(int increase);

    static int getQuntizedTimePulses(int timeInx)
    {
      int triplet = timeInx % 2 == 0 ? 2 : 3;
      return triplet * powf(2, timeInx / 2);
    }

    void syncTo(unsigned long syncTickCounter, float bpm);

    long debugTickTime = 0;
  };

  extern Clock *masterClock;
}