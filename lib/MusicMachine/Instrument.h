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
      uint8_t noteInx;
      uint8_t midiNote;
      uint8_t vel;
      uint8_t voiceIndex;
    };

    Instrument(Scheduler *runner, int voiceCount = 1);
    InstrumentDelegate *delegate;

    CircularBuffer<NoteEvent, 256> eventsBuffer;

    std::vector<Voice *> voices;
    uint8_t voiceIndex = 0;

    const int minTrigTime = 1 * TASK_MILLISECOND;
    const int maxTrigTime = 100 * TASK_MILLISECOND;

    bool isEnabled = false;
    void toggleEnabled();

    void trigNote(uint8_t midiNote = 0, uint8_t vel = 127, uint16_t noteLenght = 0, uint8_t noteInx = 0);

    virtual void noteOn(uint8_t note = 0, uint8_t vel = 127, uint8_t voiceIndex = 0);
    virtual void noteOff(uint8_t note = 0, uint8_t voiceIndex = 0);
    virtual void randomize();
    virtual void pitchBend(double val);

    long getClockTime() override;
  };
}