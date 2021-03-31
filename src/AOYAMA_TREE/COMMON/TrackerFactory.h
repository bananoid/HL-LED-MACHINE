#pragma once

#include <list>
#include <iterator>
using namespace std;

#include <Tracker.h>
#include <Track.h>
#include <Sequencer.h>
#include <MIDIInstrument.h>
using namespace HLMusicMachine;

class TrackerFactory
{
private:
  /* data */
public:
  enum TrackType
  {
    DRONE,
    BASS,
    ARP,
    CHORD,
    PAD
  };

  static void buildSong(Tracker *tracker)
  {
    Track *track;

    for (unsigned int i = 0; i < 5; i++)
    {
      TrackType type = (TrackType)i;
      int midiChannel = i + 1;

      Serial.printf("Track Type %i - midiChannel %i", type, midiChannel);

      track = new Track(tracker, new MIDIInstrument(midiChannel, tracker->runner));
      buildFactoryTrackWithSequencers(track);
      setSequncerParametersForTrackOfType(track, type);
      tracker->appendTrack(track);
    }
  }

  static void buildFactoryTrackWithSequencers(Track *track)
  {
    track->addSequencer();
    track->addSequencer();
  }

  static void setSequncerParametersForTrackOfType(Track *track, TrackType type)
  {
    Sequencer *sequencer;
    Sequencer::Parameters params;

    list<Sequencer *>::iterator it = track->sequencers.begin();

    // First Sequencer
    sequencer = *it;

    params.stepLenght = 3;
    params.retrig = -1;
    params.retrigLFO = 64;
    params.octave = 3;
    params.noteCount = 4;
    params.noteSpread = 2;
    params.steps = 32;
    params.events = 12;
    params.offset = 0;
    params.chord = 2;
    params.velocity = -1;
    params.velocityLFO = 2;
    sequencer->parameters = params;

    params.events = 1;
    params.stepLenght = 1;
    params.noteCount = 1;

    sequencer->minParameters = params;

    params.events = 16;
    params.stepLenght = 8;
    params.noteCount = 7;
    sequencer->maxParameters = params;

    sequencer->randomize();

    // First Sequencer
    it++;
    sequencer = *it;

    params.stepLenght = 3;
    params.retrig = -1;
    params.retrigLFO = 23;
    params.octave = 4;
    params.noteCount = 6;
    params.noteSpread = 2;
    params.steps = 32;
    params.events = 7;
    params.offset = 0;
    params.chord = 0;
    params.velocity = -1;
    params.velocityLFO = 4.2;

    sequencer->parameters = params;

    params.events = 1;
    params.stepLenght = 3;
    params.noteCount = 1;

    sequencer->minParameters = params;

    params.events = 16;
    params.stepLenght = 6;
    params.noteCount = 8;

    sequencer->maxParameters = params;

    sequencer->randomize();

    // switch (type)
    // {
    // case DRONE:
    // {

    //   break;
    // }
    // case BASS:
    // {
    //   break;
    // }
    // case ARP:
    // {

    //   break;
    // }
    // case CHORD:
    // {

    //   break;
    // }
    // case PAD:
    // {

    //   break;
    // }

    // default:
    //   break;
    // }
  }
};
