#pragma once

#include "config.h"
#include <TaskSchedulerDeclarations.h>

#include <vector>
#include "Voice.h"

#include <CircularBuffer.h>

namespace HLMusicMachine
{
  class InstrumentDelegate
  {
  public:
    virtual long getClockTime();
  };

  class Instrument : VoiceDelegate
  {
  private:
    int lastNote = -1;

  public:
    struct NoteEvent
    {
      uint32_t startTick;
      uint16_t noteLenght;
      uint8_t note;
      uint8_t vel;
      uint8_t voiceIndex;
    };

    Instrument(Scheduler *runner, int voiceCount = 1);
    InstrumentDelegate *delegate;

    CircularBuffer<NoteEvent, 256> eventsBuffer;

    std::vector<Voice *> voices;
    int voiceIndex = 0;

    const int minTrigTime = 1 * TASK_MILLISECOND;
    const int maxTrigTime = 100 * TASK_MILLISECOND;

    bool isEnabled = false;
    void toggleEnabled();

    void trigNote(int note = 0, int vel = 127, int noteLenght = 0);

    virtual void noteOn(int note = 0, int vel = 127, uint8_t voiceIndex = 0);
    virtual void noteOff(int note = 0, uint8_t voiceIndex = 0);
    virtual void randomize();
    virtual void pitchBend(double val);

    long getClockTime() override;
  };
}