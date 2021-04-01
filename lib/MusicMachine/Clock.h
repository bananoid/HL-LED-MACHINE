#pragma once

#include "config.h"
#include <TaskSchedulerDeclarations.h>
#include <Arduino.h>

namespace HLMusicMachine
{
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
    Clock(Scheduler *runner);

    Task clockTask;

    ClockDelegate *delegate;

    void clockTick();
    unsigned long tickCounter = 0;

    // BPM
    float getBpm();
    void setBpm(float bpm);

    float bpm = 100;
    const int clockDivider = 24;           // number of time intervals within a beat
    unsigned long clockInterval = 1000000; // default value to 1 sec
    const float minBpm = 10;
    const float maxBpm = 400;

    bool isPlaying = false;
    void play();
    void stop();
    void playStop();

    float getBpmPercentage();
    void increaseBpm(int increase);

    static int getQuntizedTimePulses(int timeInx)
    {
      int triplet = timeInx % 2 == 0 ? 1 : 3;
      return triplet * powf(2, timeInx / 2);
    }

    void syncTo(unsigned long syncTickCounter, float bpm);
  };
}