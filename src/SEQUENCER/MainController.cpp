#include "MainController.h"

#include "SerialMIDI.h"

#include <USBHost_t36.h> // access to USB MIDI devices (plugged into 2nd USB port)
USBHost myusb;
USBHub hub1(myusb);
USBHub hub2(myusb);
MIDIDevice midi1(myusb);

using namespace HLMusicMachine;

MainController::MainController(Scheduler *runner)
{
  serialMIDI.begin();

  tracker = new Tracker(runner);

  Track *track;
  Sequencer *sequencer;

  Sequencer::Parameters params;
  params.arpeggioType = Sequencer::ArpeggioType_Eucledian;

  //////////////////////////
  track = new Track(tracker, new MIDIInstrument(1, runner, 1));
  sequencer = track->addSequencer();
  cvSequencers[0] = sequencer;
  sequencer->parameters = params;
  tracker->appendTrack(track);
  track->play();

  //////////////////////////
  track = new Track(tracker, new MIDIInstrument(2, runner, 1));
  sequencer = track->addSequencer();
  cvSequencers[1] = sequencer;
  sequencer->parameters = params;
  tracker->appendTrack(track);
  track->play();

  //////////////////////////
  track = new Track(tracker, new MIDIInstrument(3, runner, 1));
  sequencer = track->addSequencer();
  cvSequencers[2] = sequencer;
  sequencer->parameters = params;
  tracker->appendTrack(track);
  track->play();

  //////////////////////////
  track = new Track(tracker, new MIDIInstrument(4, runner, 1));
  sequencer = track->addSequencer();
  cvSequencers[3] = sequencer;
  sequencer->parameters = params;
  tracker->appendTrack(track);
  track->play();

  // tracker->clock->play();

  //Start Stop button
  startStopButton.attach(32, INPUT_PULLUP); // USE EXTERNAL PULL-UP
  startStopButton.interval(5);
  startStopButton.setPressedState(LOW);

  myusb.begin();
}

void MainController::update()
{

  startStopButton.update();
  if (startStopButton.pressed())
  {
    tracker->clock->playStop();
    Serial.println("button press");
  }

  updateMIDI();
};

void MainController::updateMIDI()
{
  while (midi1.read())
  {
    uint8_t type = midi1.getType();
    uint8_t data1 = midi1.getData1();
    uint8_t data2 = midi1.getData2();
    uint8_t channel = midi1.getChannel();

    Serial.printf("type:%i - data1:%i - data2:%i - channel:%i  \n", type, data1, data2, channel);

    if (type == MIDIDevice::ControlChange)
    {
      if (channel == 2)
      {
        for (int i = 0; i < 4; i++)
        {
          int startCC = 13 + (i)*2;
          ///////////////////////////////////////////
          // Control Track 1
          if (data1 == startCC) // c1 k1
          {
            cvSequencers[i]->parameters.stepLenght = map((float)data2, 0.f, 127.f, 1.f, 9.f);
            Serial.printf("stepLenght %i \n", cvSequencers[i]->parameters.stepLenght);
          }
          else if (data1 == startCC + 16) // c1 k2
          {
            cvSequencers[i]->parameters.events = map((float)data2, 0.f, 127.f, 1.f, 16.f);
            Serial.printf("events %i \n", cvSequencers[i]->parameters.events);
          }
          else if (data1 == startCC + 36) // c1 k3
          {
            cvSequencers[i]->parameters.offset = map((float)data2, 0.f, 127.f, 0.f, 16.f);
            Serial.printf("offset %i \n", cvSequencers[i]->parameters.offset);
          }
          else if (data1 == startCC + 64) // c1 s4
          {
            cvSequencers[i]->parameters.octave = map((float)data2, 0.f, 127.f, -1.f, 4.f);
            Serial.printf("octave %i \n", cvSequencers[i]->parameters.octave);
          }
          else if (data1 == startCC + 1) // c2 k1
          {
            cvSequencers[i]->parameters.retrig = map((float)data2, 0.f, 127.f, 0.f, 7.f);
            Serial.printf("retrig %i \n", cvSequencers[i]->parameters.retrig);
          }
          else if (data1 == startCC + 17) // c2 k2
          {
            cvSequencers[i]->parameters.noteSpread = map((float)data2, 0.f, 127.f, 1.f, 5.f);
            Serial.printf("noteSpread %i \n", cvSequencers[i]->parameters.noteSpread);
          }
          else if (data1 == startCC + 37) // c2 k3
          {
            cvSequencers[i]->parameters.noteCount = map((float)data2, 0.f, 127.f, 1.f, 5.f);
            Serial.printf("noteCount %i \n", cvSequencers[i]->parameters.noteCount);
          }
          else if (data1 == startCC + 65) // c2 s4
          {
            cvSequencers[i]->parameters.noteOffset = map((float)data2, 0.f, 127.f, 0.f, 6.f);
            Serial.printf("noteOffset %i \n", cvSequencers[i]->parameters.noteOffset);
          }
        }
      }
    }
  }
}