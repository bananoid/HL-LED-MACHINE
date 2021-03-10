#pragma once

#include <Encoder.h>
#include <Bounce2.h>
#include <FastLED.h>

#include "Instrument.h"
#include "config.h"
#include <TaskSchedulerDeclarations.h>

class UIDelegate
{
public:
  // virtual void clockTick(); // virtual because it is not implemented in the class
  virtual void changeBpm(float bpm);
  virtual void increaseBpm(int increase);
  virtual void increaseTrigTime(int increase);
  virtual void increaseTrigPWM(int increase);
  virtual float getBpmPercentage();
  virtual void playStop();

  virtual float getTrigTimePercentage();
  virtual float getTrigPWMPercentage();

  // virtual void changeInstrumentFrequency(int instrumentIndex, int frequency);
  virtual void changeInstrumentSteps(int instrumentIndex, int steps);
  virtual void changeInstrumentEvents(int instrumentIndex, int events);
  virtual void changeInstrumentOffset(int instrumentIndex, int offset);

  virtual Instrument *getInstrumentForIndex(int instrumentIndex);
  virtual int getCurrentPlayStepIndex();
};

class UI : public Task
{
private:
  bool isUIInvalid = false;

public:
  enum MainMode
  {
    instrument1,
    instrument2,
    instrument3,
    master
  };
  const int mainModeCount = 4;
  int mainMode = 0;

  enum InstrumentMode
  {
    offset,
    events,
    steps,
  };
  const int instrumentModeCount = 2;
  int instrumentMode = 1;

  enum MasterMode
  {
    bpm,
    trigTime,
    trigPWM,
  };
  const int masterModeCount = 3;
  int masterMode = 0;

  UI(Scheduler *runner);
  UIDelegate *delegate;

  bool Callback();

  Encoder *encoder;

  Bounce *encoderButton;
  Bounce *instrumentButtons[NUMBER_OF_INSTRUMENTS];

  CRGB leds[NUM_LEDS];

  void selectMainMode(MainMode mode);
  void selectNextMainMode();
  void selectPrevMainMode();
  void selectNextInstrumentMode();
  void selectNextMasterMode();
  void onEncoderRotate(int increment);

  long encoderOldPosition = -999;
  long encoderOldSnapPositon = -999;
  int encoderSnapPositonSize = 1;

  bool encoderPressRotationMode = false;
  bool encoderButtonPress = false;

  int prevPlayStepIndex = -1;

  void drawUI();
  void drawInstrument();
  void drawMaster();

  void update();
};
