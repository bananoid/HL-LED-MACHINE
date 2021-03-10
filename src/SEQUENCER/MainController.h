#pragma once //to prevent reimport (singleton)

#include "Clock.h"
#include "Instrument.h"
#include "UI.h"

class MainController : public ClockDelegate, public UIDelegate, public InstrumentDelegate
{
private:
    /* data */
public:
    MainController(Scheduler *runner);

    void update();

    void play();
    void stop();
    bool isPlaying = false;

    void clockTick() override;

    void changeBpm(float bpm) override;
    void increaseBpm(int increase) override;
    void increaseTrigTime(int increase) override;
    void increaseTrigPWM(int increase) override;
    float getTrigTimePercentage() override;
    float getTrigPWMPercentage() override;
    float getBpmPercentage() override;
    void playStop() override;

    // void changeInstrumentFrequency(int instrumentIndex, int frequency) override;
    void changeInstrumentEvents(int instrumentIndex, int events) override;
    void changeInstrumentSteps(int instrumentIndex, int steps) override;
    void changeInstrumentOffset(int instrumentIndex, int offset) override;

    long getClockTime() override;

    Instrument *getInstrumentForIndex(int instrumentIndex) override;
    int getCurrentPlayStepIndex() override;

    UI *ui;
    Clock *clock;
    Instrument *instruments[NUMBER_OF_INSTRUMENTS];
};
