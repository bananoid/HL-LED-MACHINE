#pragma once

#include <Arduino.h>

#include "config.h"
#include <TaskSchedulerDeclarations.h>
#include "Clock.h"
#include <LinkedList.h>
#include "Track.h"

namespace HLSequencer
{
  class Sequencer : public ClockDelegate, public InstrumentDelegate
  {
  private:
    LinkedList<Track *> *tracks;

  public:
    Sequencer(Scheduler *runner);

    Clock *clock;
    void clockTick() override;

    void appendTrack(Track *track);

    long getClockTime() override;
  };
}