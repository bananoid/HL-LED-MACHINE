
#include "config.h"
#include "MainController.h"
#include <TaskScheduler.h>
#include "SerialMIDI.h"
#include "Clock.h"

Scheduler runner;
MainController *mainController;
using namespace HLMusicMachine;

// #include "TeensyDebug.h"
// #pragma GCC optimize("O0")

// #define MEMORY_MONITOR

#ifdef MEMORY_MONITOR
#include <RamMonitor.h>
RamMonitor ram;
uint32_t reporttime;

void report_ram_stat(const char *aname, uint32_t avalue)
{
    Serial.print(aname);
    Serial.print(": ");
    Serial.print((avalue + 512) / 1024);
    Serial.print(" Kb (");
    Serial.print((((float)avalue) / ram.total()) * 100, 1);
    Serial.println("%)");
};

void report_ram()
{
    bool lowmem;
    bool crash;

    Serial.println("==== memory report ====");

    report_ram_stat("free", ram.adj_free());
    report_ram_stat("stack", ram.stack_total());
    report_ram_stat("heap", ram.heap_total());

    lowmem = ram.warning_lowmem();
    crash = ram.warning_crash();
    if (lowmem || crash)
    {
        Serial.println();

        if (crash)
            Serial.println("**warning: stack and heap crash possible");
        else if (lowmem)
            Serial.println("**warning: unallocated memory running low");
    };

    Serial.println();
};
#endif

void externalClock()
{
    // Serial.println("Clock in");
    mainController->tracker->clock->tick();
}

void externalStart()
{
    // Serial.println("External Start");
    mainController->tracker->clock->play();
}

void externalStop()
{
    // Serial.println("External Stop");
    mainController->tracker->clock->stop();
}

void setup()
{
    // debug.begin(SerialUSB1);

#ifdef MEMORY_MONITOR
    ram.initialize();
    reporttime = millis();
#endif
    Serial.begin(115200);
    mainController = new MainController(&runner);
    // serialMIDI.ports[2]->setHandleClock(externalClock);
    // serialMIDI.ports[2]->setHandleStart(externalStart);
    // serialMIDI.ports[2]->setHandleStop(externalStop);
}

void loop()
{
#ifdef MEMORY_MONITOR
    uint32_t time = millis();
    if ((time - reporttime) > 2000)
    {
        reporttime = time;
        report_ram();
    };
    ram.run();
#endif

    mainController->update();
    runner.execute();
    // serialMIDI.update();
}
