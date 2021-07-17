#include "MainController.h"

#include "SerialMIDI.h"
#include "Storage.h"
#include <USBHost_t36.h> // access to USB MIDI devices (plugged into 2nd USB port)
USBHost myusb;
USBHub hub1(myusb);
USBHub hub2(myusb);
MIDIDevice midi1(myusb);

using namespace HLMusicMachine;

#include <MathUtils.h>

MainController::MainController(Scheduler *runner)
{

  storage->begin(runner);
  serialMIDI.begin();

  midiUIDrawTask.set(TASK_MILLISECOND * 20, TASK_FOREVER, [this]()
                     { drawMidiInterface(); });
  runner->addTask(midiUIDrawTask);
  midiUIDrawTask.enable();

  tracker = new Tracker(runner);

  Track *track;
  Sequencer *sequencer;

  Parameters params;
  params.arpeggioType = ArpeggioType_Eucledian;
  // params.arpeggioType = ArpeggioType_LFO;
  params.arpeggioLFO = 3;

  for (int i = 0; i < NUM_OF_CV_TRAKS; i++)
  {

    int channel = i + 1;
    //////////////////////////
    track = new Track(tracker, new MIDIInstrument(channel, runner, 1));
    sequencer = track->addSequencer();
    cvSequencers[i] = sequencer;
    cvTracks[i] = track;
    sequencer->parameters = params;
    tracker->appendTrack(track);
    track->stop();
  }

  for (int i = 0; i < NUM_OF_MIDI_TRAKS; i++)
  {
    int channel = i + 1;
    //////////////////////////
    track = new Track(tracker, new MIDIInstrument(channel, runner, 3, 2));
    sequencer = track->addSequencer();
    midiSequencers[i] = sequencer;
    midiTracks[i] = track;
    sequencer->parameters = params;
    sequencer->parameters.chord = 3;
    tracker->appendTrack(track);
    track->stop();
  }

  tracker->clock->setBpm(100);
  // tracker->clock->play();

  myusb.begin();

  // loadGlobalSettings();

  // delay(2000);
  // midiUIInvalid = true;

  ui->init(runner, tracker);
  ui->delegate = this;
}

void MainController::update()
{
  updateMIDI();
};

void MainController::updateMIDI()
{
  while (midi1.read())
  {
    if (millis() < 3000)
    {
      return;
    }

    midiUIInvalid = true;

    uint8_t type = midi1.getType();
    uint8_t data1 = midi1.getData1();
    uint8_t data2 = midi1.getData2();
    uint8_t channel = midi1.getChannel();

    Serial.printf("type:%i - data1:%i - data2:%i - channel:%i  \n", type, data1, data2, channel);
    if (channel == 1)
    {
      if (type == MIDIDevice::ControlChange)
      {
        if (data1 == 50) // c1 s4
        {
          tracker->quantizer->noteOffset.setValue((float)data2, 0.f, 127.f);
        }

        if (data1 == 53)
        {
          // tracker->quantizer->toggleRecordingNoteOffset();
          tracker->quantizer->setRecordingNoteOffset(data2 == 0 ? false : true);
        }
      }
    }

    // load
    if (data1 == 106 && type == MIDIDevice::NoteOn)
    {
      ui->loadProject();
    }

    // Save
    if (data1 == 107 && type == MIDIDevice::NoteOn)
    {
      ui->saveProject();
    }

    // Track Selection next button
    // Next project Slot
    if (data2 == 0 && data1 == 107 && type == MIDIDevice::ControlChange)
    {
      storage->projectsBank->currentSlot += 1;
    }

    // Track Selection prev button
    // Prev project Slot
    if (data2 == 0 && data1 == 106 && type == MIDIDevice::ControlChange)
    {
      storage->projectsBank->currentSlot -= 1;
    }

    // Start Stop
    if (data1 == 108 && type == MIDIDevice::NoteOn)
    {
      tracker->clock->playStop();
      midiUIInvalid = true;
    }

    for (int i = 0; i < NUM_OF_SCALES; i++)
    {
      if (data1 == (73 + i) && type == MIDIDevice::NoteOn)
      {
        tracker->setScaleIndex(i);
        midiUIInvalid = true;
      }
    }

    for (int i = 0; i < NUM_OF_SCALES; i++)
    {
      if (data1 == (41 + i) && type == MIDIDevice::NoteOn)
      {
        tracker->setKeyIndex(i);
        midiUIInvalid = true;
      }
    }

    if (channel == 2)
    {

      for (int i = 0; i < NUM_OF_CV_TRAKS; i++)
      {
        if (type == MIDIDevice::ControlChange)
        {
          int startCC = 13 + (i)*2;
          ///////////////////////////////////////////
          // Control Track 1
          if (data1 == startCC) // c1 k1
          {
            cvSequencers[i]->parameters.stepLenght.setValue((float)data2, 0.f, 127.f);
            // Serial.printf("stepLenght %i \n", cvSequencers[i]->parameters.stepLenght);
          }
          else if (data1 == startCC + 16) // c1 k2
          {
            cvSequencers[i]->parameters.events.setValue((float)data2, 0.f, 127.f);
            // Serial.printf("events %i \n", cvSequencers[i]->parameters.events);
          }
          else if (data1 == startCC + 36) // c1 k3
          {
            cvSequencers[i]->parameters.offset.setValue((float)data2, 0.f, 127.f);
            // Serial.printf("offset %i \n", cvSequencers[i]->parameters.offset);
          }
          else if (data1 == startCC + 64) // c1 s4
          {
            cvSequencers[i]->parameters.octave.setValue((float)data2, 0.f, 127.f);
            // Serial.printf("octave %i \n", cvSequencers[i]->parameters.octave);
          }
          else if (data1 == startCC + 1) // c2 k1
          {
            cvSequencers[i]->parameters.retrig.setValue((float)data2, 0.f, 127.f);
            // Serial.printf("retrig %i \n", cvSequencers[i]->parameters.retrig);
          }
          else if (data1 == startCC + 17) // c2 k2
          {
            cvSequencers[i]->parameters.noteSpread.setValue((float)data2, 0.f, 127.f);
            // Serial.printf("noteSpread %i \n", cvSequencers[i]->parameters.noteSpread);
          }
          else if (data1 == startCC + 37) // c2 k3
          {
            cvSequencers[i]->parameters.noteCount.setValue((float)data2, 0.f, 127.f);
            // Serial.printf("noteCount %i \n", cvSequencers[i]->parameters.noteCount);
          }
          else if (data1 == startCC + 65) // c2 s4
          {
            cvSequencers[i]->parameters.noteOffset.setValue((float)data2, 0.f, 127.f);
            // Serial.printf("noteOffset %i \n", cvSequencers[i]->parameters.noteOffset);
          }
        }

        // ON/OFF buttons
        if (data1 == 57 + i)
        {
          if (type == MIDIDevice::NoteOn)
          {
            cvTracks[i]->togglePlayStop();
            midiUIInvalid = true;
          }
        }
      }
    }

    // MIDI Instruments Tracks

    if (channel == 3)
    {
      for (int i = 0; i < NUM_OF_MIDI_TRAKS; i++)
      {
        if (type == MIDIDevice::ControlChange)
        {
          int startCC = 13 + (i)*2;
          ///////////////////////////////////////////
          // Control Track 1
          if (data1 == startCC) // c1 k1
          {
            midiSequencers[i]->parameters.stepLenght.setValue((float)data2, 0.f, 127.f);
            // Serial.printf("stepLenght %i \n", midiSequencers[i]->parameters.stepLenght);
          }
          else if (data1 == startCC + 16) // c1 k2
          {
            midiSequencers[i]->parameters.events.setValue((float)data2, 0.f, 127.f);
            // Serial.printf("events %i \n", midiSequencers[i]->parameters.events);
          }
          else if (data1 == startCC + 36) // c1 k3
          {
            midiSequencers[i]->parameters.offset.setValue((float)data2, 0.f, 127.f);
            // Serial.printf("offset %i \n", midiSequencers[i]->parameters.offset);
          }
          else if (data1 == startCC + 64) // c1 s4
          {
            midiSequencers[i]->parameters.octave.setValue((float)data2, 0.f, 127.f);
            // Serial.printf("octave %i \n", midiSequencers[i]->parameters.octave);
          }
          else if (data1 == startCC + 1) // c2 k1
          {
            midiSequencers[i]->parameters.retrig.setValue((float)data2, 0.f, 127.f);
            // Serial.printf("retrig %i \n", midiSequencers[i]->parameters.retrig);
          }
          else if (data1 == startCC + 17) // c2 k2
          {
            midiSequencers[i]->parameters.noteSpread.setValue((float)data2, 0.f, 127.f);
            // Serial.printf("noteSpread %i \n", midiSequencers[i]->parameters.noteSpread);
          }
          else if (data1 == startCC + 37) // c2 k3
          {
            midiSequencers[i]->parameters.noteCount.setValue((float)data2, 0.f, 127.f);
            // Serial.printf("noteCount %i \n", midiSequencers[i]->parameters.noteCount);
          }
          else if (data1 == startCC + 65) // c2 s4
          {
            midiSequencers[i]->parameters.noteOffset.setValue((float)data2, 0.f, 127.f);
            // Serial.printf("noteOffset %i \n", midiSequencers[i]->parameters.noteOffset);
          }
        }

        // ON/OFF buttons
        if (data1 == 57 + i)
        {
          if (type == MIDIDevice::NoteOn)
          {
            midiTracks[i]->togglePlayStop();
            midiUIInvalid = true;
          }
        }
      }
    }
  }
}

void MainController::drawMidiInterface()
{
  if (!midiUIInvalid)
  {
    return;
  }
  midiUIInvalid = false;
  for (int i = 0; i < NUM_OF_CV_TRAKS; i++)
  {
    midi1.sendNoteOn(57 + i, cvTracks[i]->isPlaying ? 127 : 0, 2);
  }
  for (int i = 0; i < NUM_OF_MIDI_TRAKS; i++)
  {
    midi1.sendNoteOn(57 + i, midiTracks[i]->isPlaying ? 127 : 0, 3);
  }

  midi1.sendNoteOn(108, tracker->clock->isPlaying ? 127 : 0, 1);
  midi1.sendNoteOn(108, tracker->clock->isPlaying ? 127 : 0, 2);
  midi1.sendNoteOn(108, tracker->clock->isPlaying ? 127 : 0, 3);

  for (int i = 0; i < 4; i++)
  {
    midi1.sendNoteOn(73 + i, tracker->scaleIndex == i ? 127 : 0, 1);
    midi1.sendNoteOn(41 + i, tracker->keyIndex == i ? 127 : 0, 1);
    midi1.sendNoteOn(73 + i, tracker->scaleIndex == i ? 127 : 0, 2);
    midi1.sendNoteOn(41 + i, tracker->keyIndex == i ? 127 : 0, 2);
    midi1.sendNoteOn(73 + i, tracker->scaleIndex == i ? 127 : 0, 3);
    midi1.sendNoteOn(41 + i, tracker->keyIndex == i ? 127 : 0, 3);
  }

  midi1.sendControlChange(53, tracker->quantizer->isRecording, 1);

  // Serial.println("midi ui redraw");
  // saveGlobalSettings();
}
