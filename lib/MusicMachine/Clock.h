#pragma once

#include <Arduino.h>

#include <MIDI.h>

namespace HLMusicMachine
{
  void timerTick();
  class ClockDelegate
  {
  public:
    virtual void clockTick(){};
    virtual void clockStart(){};
    virtual void clockStop(){};
  };
  class Clock
  {
  private:
  public:
    Clock();

    void begin();

    IntervalTimer timer;

    bool externalClock = false;
    void tick();

    ClockDelegate *delegate = nullptr;

    // const int clockLedPort = 13; //31
    const int clockLedPort = 40; //31
    void clockTick();
    unsigned long tickCounter = 0;
    unsigned long prevClickTime = 0;

    // BPM
    float getBpm();
    void setBpm(float bpm);

    float bpm = 100;
    const int clockDivider = 24;           // number of time intervals within a beat
    unsigned long clockInterval = 1000000; // default value to 1 sec
    const float minBpm = 1;
    const float maxBpm = 300;

    bool isPlaying = false;
    void play();
    void stop();
    void playStop();

    float getBpmPercentage();
    void increaseBpm(int increase);

    static int getQuntizedTimePulses(int timeInx)
    {
      if (timeInx <= 0)
      {
        return 1;
      }

      timeInx = timeInx - 1;
      int triplet = (timeInx) % 2 == 0 ? 2 : 3;
      return triplet * powf(2, timeInx / 2);
    }

    void syncTo(unsigned long syncTickCounter, float bpm);

    long debugTickTime = 0;
  };

  extern Clock *masterClock;
}