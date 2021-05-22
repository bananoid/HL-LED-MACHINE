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

class SerialMIDI
{
private:
public:
  MidiInterface *ports[MIDI_PORT_COUNT];

  SerialMIDI()
  {
    ports[0] = new MidiInterface(*new MidiTransport(Serial1));
    ports[1] = new MidiInterface(*new MidiTransport(Serial2));
    ports[2] = new MidiInterface(*new MidiTransport(Serial3));
    ports[3] = new MidiInterface(*new MidiTransport(Serial4));
    ports[4] = new MidiInterface(*new MidiTransport(Serial5));
    ports[5] = new MidiInterface(*new MidiTransport(Serial6));
    ports[6] = new MidiInterface(*new MidiTransport(Serial7));
    ports[7] = new MidiInterface(*new MidiTransport(Serial8));
  };

  ~SerialMIDI(){};

  void begin()
  {
    ports[1]->begin(MIDI_CHANNEL_OMNI);
    ports[1]->turnThruOff();

    ports[2]->begin(MIDI_CHANNEL_OMNI);
    ports[2]->turnThruOff();
  }
};

extern SerialMIDI serialMIDI;
