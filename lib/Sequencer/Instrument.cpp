#include "Instrument.h"
#include <Arduino.h>

Instrument::Instrument(int pin, Scheduler *runner) : Task(TASK_MILLISECOND * 100, TASK_FOREVER, runner, false)
{
    this->pin = pin;
    pinMode(pin, OUTPUT);

    disable();
}

bool Instrument::Callback()
{

    trig(false);
    disable();
}

void Instrument::togglePlayPause()
{
    isPlaying = !isPlaying;
}

bool Instrument::isEuclidianSeq(int index)
{
    // return index % events == 0;
    // given a euclidian sequence, represented by steps, events, offset,
    // and an index, return if the index is a '1' in the sequence
    if (events == 0)
    {
        return false;
    }
    int x = (index + steps * 2 - offset) % steps;
    float step = (float)steps / (float)events;
    float fMod = fmodf(x, step);

    return floor(fMod) == 0;
}

void Instrument::trig(bool on)
{
    // digitalWrite(pin, on);

    if(on){
        analogWrite(pin, trigPWM);
    }else{
        analogWrite(pin, 0);
    }

    if (on)
    {
        long trigTime = min(delegate->getClockTime() * 0.9, this->trigTime);
        restartDelayed(trigTime);
        // Serial.printf("instrument Node on %i time: %i override time: %i\n", pin, this->trigTime, trigTime);
    }
};
