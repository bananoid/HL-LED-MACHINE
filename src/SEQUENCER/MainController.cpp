#include "MainController.h"

MainController::MainController(Scheduler *runner)
{
    sequencer = new Sequencer(runner);
}

void MainController::update(){};
