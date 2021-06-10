#pragma once

#include <MIDI.h>
#include <Arduino.h>

#define MIDI_PORT_COUNT 6

enum MidiPort
{
  MIDI_PORT_1,
  MIDI_PORT_2,
  MIDI_PORT_3,
  MIDI_PORT_4,
  MIDI_PORT_5,
  MIDI_PORT_6,
  MIDI_PORT_7,
  MIDI_PORT_8,
};

using MidiTransport = MIDI_NAMESPACE::SerialMIDI<HardwareSerial>;
using MidiInterface = MIDI_NAMESPACE::MidiInterface<MidiTransport>;

#define MIDI_PORT_ENABLE_FIRST 1
#define MIDI_PORT_ENABLE_LAST 3

class SerialMIDI
{
private:
public:
  MidiInterface *ports[MIDI_PORT_COUNT];
  HardwareSerial *serials[8] = {&Serial1, &Serial2, &Serial3, &Serial4, &Serial5, &Serial6, &Serial7, &Serial8};

  SerialMIDI()
  {
    for (int i = MIDI_PORT_ENABLE_FIRST; i < MIDI_PORT_ENABLE_LAST; i++)
    {
      ports[i] = new MidiInterface(*new MidiTransport(*serials[i]));
    }
  };

  ~SerialMIDI(){};

  void begin()
  {
    for (int i = MIDI_PORT_ENABLE_FIRST; i < MIDI_PORT_ENABLE_LAST; i++)
    {
      ports[i]->begin(MIDI_CHANNEL_OMNI);
      ports[i]->turnThruOff();
    }
  }

  void update()
  {
    for (int i = MIDI_PORT_ENABLE_FIRST; i < MIDI_PORT_ENABLE_LAST; i++)
    {
      ports[i]->read();
    }
  }

  void clockStart()
  {
    for (int i = MIDI_PORT_ENABLE_FIRST; i < MIDI_PORT_ENABLE_LAST; i++)
    {
      ports[i]->sendRealTime(midi::Start);
      // ports[i]->sendStart();
    }
  }

  void clockStop()
  {
    for (int i = MIDI_PORT_ENABLE_FIRST; i < MIDI_PORT_ENABLE_LAST; i++)
    {
      ports[i]->sendRealTime(midi::Stop);
      // ports[i]->sendStop();
    }
  }

  void clockTick()
  {
    for (int i = MIDI_PORT_ENABLE_FIRST; i < MIDI_PORT_ENABLE_LAST; i++)
    {
      ports[i]->sendRealTime(midi::Clock);
      // ports[i]->sendClock();
      // serials[i]->flush();
      // serials[i]->clear();
    }
  }

  void sendTestNotes(bool on)
  {
    for (int i = MIDI_PORT_ENABLE_FIRST; i < MIDI_PORT_ENABLE_LAST; i++)
    {
      if (on)
      {
        ports[i]->sendNoteOn(60, 127, 1);
        ports[i]->sendNoteOn(60, 127, 2);
        ports[i]->sendNoteOn(60, 127, 3);
        ports[i]->sendNoteOn(60, 127, 4);
      }
      else
      {
        ports[i]->sendNoteOff(60, 127, 1);
        ports[i]->sendNoteOff(60, 127, 2);
        ports[i]->sendNoteOff(60, 127, 3);
        ports[i]->sendNoteOff(60, 127, 4);
      }
    }
  }
};

extern SerialMIDI serialMIDI;
