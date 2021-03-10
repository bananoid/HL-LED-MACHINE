#include "MainController.h"
#include <Arduino.h>
#include "Instrument.h"
#include "config.h"

MainController::MainController(Scheduler *runner)
{
    clock = new Clock(runner);
    clock->delegate = this;

    ui = new UI(runner);
    ui->enable();
    ui->delegate = this;

    for (int i = 0; i < NUMBER_OF_INSTRUMENTS; i++)
    {
        instruments[i] = new Instrument(instrumentPins[i], runner);
        instruments[i]->delegate = this;
    }

    play();
}

void MainController::update()
{
    ui->update();
};

void MainController::play()
{
    isPlaying = true;
    Serial.println("Play");

    clock->tickCounter = 0;
    clock->setInterval(clock->clockInterval);
    clock->enable();
};

void MainController::stop()
{
    isPlaying = false;
    Serial.println("Stop");

    clock->disable();
};

Instrument *MainController::getInstrumentForIndex(int instrumentIndex)
{

    return instruments[instrumentIndex];
}

// Clock
void MainController::clockTick()
{
    // Serial.printf("Tick %lu\n", clock->tickCounter);
    for (int i = 0; i < NUMBER_OF_INSTRUMENTS; i++)
    {
        if (!instruments[i]->isPlaying)
        {
            continue;
        }

        if (instruments[i]->isEuclidianSeq(clock->tickCounter))
        {
            instruments[i]->trig(true);
        }
    }
};

void MainController::changeInstrumentEvents(int instrumentIndex, int events)
{
    Instrument *instrument = instruments[instrumentIndex];
    events = map(events, 0, 127, instrument->minEvents, instrument->maxEvents);
    instrument->events = events;
    Serial.printf("events for instrument %i is %i\n", instrumentIndex, events);
};

void MainController::changeInstrumentSteps(int instrumentIndex, int steps)
{
    Instrument *instrument = instruments[instrumentIndex];
    steps = map(steps, 0, 127, instrument->minSteps, instrument->maxSteps);
    instrument->steps = steps;
    Serial.printf("steps for instrument %i is %i\n", instrumentIndex, steps);
};

void MainController::changeInstrumentOffset(int instrumentIndex, int offset)
{
    Instrument *instrument = instruments[instrumentIndex];
    offset = map(offset, 0, 127, instrument->minOffset, instrument->maxOffset);
    instrument->offset = offset;
    Serial.printf("offset for instrument %i is %i\n", instrumentIndex, offset);
};

void MainController::changeBpm(float bpm)
{
    clock->setBpm(bpm);
};

float MainController::getBpmPercentage()
{
    return map(clock->getBpm(), clock->minBpm, clock->maxBpm, 0.0, 1.0);
}

void MainController::increaseBpm(int increase)
{
    float bpm = clock->getBpm() + increase;
    clock->setBpm(bpm);
}
void MainController::increaseTrigTime(int increase)
{
    for (int i = 0; i < NUMBER_OF_INSTRUMENTS; i++)
    {
        instruments[i]->trigTime += increase * 1000;
        instruments[i]->trigTime = constrain(
            instruments[i]->trigTime,
            instruments[i]->minTrigTime,
            instruments[i]->maxTrigTime);
    }

    Serial.printf("trigTime :%i\n", instruments[0]->trigTime);
}
void MainController::increaseTrigPWM(int increase)
{
    for (int i = 0; i < NUMBER_OF_INSTRUMENTS; i++)
    {
        instruments[i]->trigPWM += increase * 2;
        instruments[i]->trigPWM = constrain(
            instruments[i]->trigPWM,
            instruments[i]->minTrigPWM,
            instruments[i]->maxTrigPWM);
    }

    Serial.printf("trigTime :%i\n", instruments[0]->trigPWM);
}

float MainController::getTrigTimePercentage()
{
    float perc = map(
        (float)instruments[0]->trigTime,
        (float)instruments[0]->minTrigTime,
        (float)instruments[0]->maxTrigTime,
        0.0f, 1.0f);
    return perc;
}

float MainController::getTrigPWMPercentage()
{
    float perc = map(
        (float)instruments[0]->trigPWM,
        (float)instruments[0]->minTrigPWM,
        (float)instruments[0]->maxTrigPWM,
        0.0f, 1.0f);
    return perc;
}

void MainController::playStop()
{
    if (isPlaying)
    {
        stop();
    }
    else
    {
        play();
    }
};

long MainController::getClockTime()
{
    return clock->clockInterval;
}

int MainController::getCurrentPlayStepIndex()
{
    return clock->tickCounter % 16;
}