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

  Sequencer::Parameters params;
  params.arpeggioType = Sequencer::ArpeggioType_Eucledian;
  // params.arpeggioType = Sequencer::ArpeggioType_LFO;
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
    track->play();
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
    track->play();
  }

  tracker->clock->setBpm(120);
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
    globalSettingsUnsaved = true;

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
          float bpm = MathUtils::scale((float)data2, 0.f, 127.f, 30.f, 300.f);
          tracker->clock->setBpm(bpm);
          Serial.println(bpm);
        }
      }
    }

    // load
    if (data1 == 106 && type == MIDIDevice::NoteOn)
    {
      loadGlobalSettings();
    }

    // Save
    if (data1 == 107 && type == MIDIDevice::NoteOn)
    {
      saveGlobalSettings();
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
            cvSequencers[i]->parameters.stepLenght = MathUtils::scale((float)data2, 0.f, 127.f, 9.f, 1.f);
            // Serial.printf("stepLenght %i \n", cvSequencers[i]->parameters.stepLenght);
          }
          else if (data1 == startCC + 16) // c1 k2
          {
            cvSequencers[i]->parameters.events = MathUtils::scale((float)data2, 0.f, 127.f, 1.f, 16.f);
            // Serial.printf("events %i \n", cvSequencers[i]->parameters.events);
          }
          else if (data1 == startCC + 36) // c1 k3
          {
            cvSequencers[i]->parameters.offset = MathUtils::scale((float)data2, 0.f, 127.f, 0.f, 16.f);
            // Serial.printf("offset %i \n", cvSequencers[i]->parameters.offset);
          }
          else if (data1 == startCC + 64) // c1 s4
          {
            cvSequencers[i]->parameters.octave = MathUtils::scale((float)data2, 0.f, 127.f, -1.f, 4.f);
            // Serial.printf("octave %i \n", cvSequencers[i]->parameters.octave);
          }
          else if (data1 == startCC + 1) // c2 k1
          {
            cvSequencers[i]->parameters.retrig = MathUtils::scale((float)data2, 0.f, 127.f, 0.f, 7.f);
            // Serial.printf("retrig %i \n", cvSequencers[i]->parameters.retrig);
          }
          else if (data1 == startCC + 17) // c2 k2
          {
            cvSequencers[i]->parameters.noteSpread = MathUtils::scale((float)data2, 0.f, 127.f, 1.f, 5.f);
            // Serial.printf("noteSpread %i \n", cvSequencers[i]->parameters.noteSpread);
          }
          else if (data1 == startCC + 37) // c2 k3
          {
            cvSequencers[i]->parameters.noteCount = MathUtils::scale((float)data2, 0.f, 127.f, 1.f, 7.f);
            // Serial.printf("noteCount %i \n", cvSequencers[i]->parameters.noteCount);
          }
          else if (data1 == startCC + 65) // c2 s4
          {
            cvSequencers[i]->parameters.noteOffset = MathUtils::scale((float)data2, 0.f, 127.f, 0.f, 6.f);
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
            midiSequencers[i]->parameters.stepLenght = MathUtils::scale((float)data2, 0.f, 127.f, 9.f, 1.f);
            Serial.printf("stepLenght %i \n", midiSequencers[i]->parameters.stepLenght);
          }
          else if (data1 == startCC + 16) // c1 k2
          {
            midiSequencers[i]->parameters.events = MathUtils::scale((float)data2, 0.f, 127.f, 1.f, 16.f);
            Serial.printf("events %i \n", midiSequencers[i]->parameters.events);
          }
          else if (data1 == startCC + 36) // c1 k3
          {
            midiSequencers[i]->parameters.offset = MathUtils::scale((float)data2, 0.f, 127.f, 0.f, 16.f);
            Serial.printf("offset %i \n", midiSequencers[i]->parameters.offset);
          }
          else if (data1 == startCC + 64) // c1 s4
          {
            midiSequencers[i]->parameters.octave = MathUtils::scale((float)data2, 0.f, 127.f, -1.f, 4.f);
            Serial.printf("octave %i \n", midiSequencers[i]->parameters.octave);
          }
          else if (data1 == startCC + 1) // c2 k1
          {
            midiSequencers[i]->parameters.retrig = MathUtils::scale((float)data2, 0.f, 127.f, 0.f, 7.f);
            Serial.printf("retrig %i \n", midiSequencers[i]->parameters.retrig);
          }
          else if (data1 == startCC + 17) // c2 k2
          {
            midiSequencers[i]->parameters.noteSpread = MathUtils::scale((float)data2, 0.f, 127.f, 1.f, 5.f);
            Serial.printf("noteSpread %i \n", midiSequencers[i]->parameters.noteSpread);
          }
          else if (data1 == startCC + 37) // c2 k3
          {
            midiSequencers[i]->parameters.noteCount = MathUtils::scale((float)data2, 0.f, 127.f, 1.f, 7.f);
            Serial.printf("noteCount %i \n", midiSequencers[i]->parameters.noteCount);
          }
          else if (data1 == startCC + 65) // c2 s4
          {
            midiSequencers[i]->parameters.noteOffset = MathUtils::scale((float)data2, 0.f, 127.f, 0.f, 6.f);
            Serial.printf("noteOffset %i \n", midiSequencers[i]->parameters.noteOffset);
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

  midi1.sendNoteOn(107, globalSettingsUnsaved ? 127 : 0, 1);
  midi1.sendNoteOn(107, globalSettingsUnsaved ? 127 : 0, 2);
  midi1.sendNoteOn(107, globalSettingsUnsaved ? 127 : 0, 3);

  // Serial.println("midi ui redraw");
  // saveGlobalSettings();
}

void MainController::saveGlobalSettings()
{
  for (int i = 0; i < NUM_OF_CV_TRAKS; i++)
  {
    memcpy(&globalSettings.trackParams[i], &cvSequencers[i]->parameters, sizeof(Sequencer::Parameters));
    globalSettings.tracksEnabled[i] = cvTracks[i]->isPlaying;
  }
  Serial.printf("all params size = %i \n", sizeof(cvSequencers[0]->parameters));
  Serial.printf("steps param size = %i \n", sizeof(cvSequencers[0]->parameters.steps));

  storage->save((uint8_t *)&globalSettings, sizeof(GlobalSettings));

  globalSettingsUnsaved = false;
}

void MainController::loadGlobalSettings()
{
  storage->load((uint8_t *)&globalSettings, sizeof(GlobalSettings));

  for (int i = 0; i < NUM_OF_CV_TRAKS; i++)
  {
    memcpy(&cvSequencers[i]->parameters, &globalSettings.trackParams[i], sizeof(Sequencer::Parameters));
    globalSettings.tracksEnabled[i] ? cvTracks[i]->play() : cvTracks[i]->stop();

    // Overide Not assigned parameters
    // Todo: add controls
    cvSequencers[i]->parameters.velocity = -1;
    cvSequencers[i]->parameters.velocityLFO = 4;
    cvSequencers[i]->parameters.velocityLFO.min = 0;
    cvSequencers[i]->parameters.velocityLFO.max = 127;

    cvSequencers[i]->parameters.arpeggioType = Sequencer::ArpeggioType_LFO;
    cvSequencers[i]->parameters.arpeggioLFO = 1;

    cvSequencers[i]->parameters.fillFactor = 1;
  }

  globalSettingsUnsaved = false;
}

void MainController::frontLeftButtonClick()
{
  // loadGlobalSettings();
  // Serial.println("frontLeftButtonClick");

  tracker->clock->playStop();
}