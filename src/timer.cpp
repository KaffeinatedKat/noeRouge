#include "timer.h"

// Todo list:
//
// 00 - #define FRAMERATE instead of magic number

// ----- timerObject -----

void timerObject::onTick() {
    // Do nothing if the timer has run out
    if (this->isOver) {
        std::cout << "I am a timer who's time has run out\n";
        return;
    }
    std::cout << "I am a timer who is counting down: " << this->secondsRemaining << std::endl;

    this->ticksRemaining--;
    this->secondsRemaining = (this->ticksRemaining / 60) + 1;
    this->timeElapsed = this->totalTime - this->secondsRemaining;

    if (this->ticksRemaining == 0) {
        this->isOver = true;
    }

    return;
}

bool timerObject::isTimerDone() {
    return this->isOver;
}

void timerObject::setTimer(int seconds) {
    this->totalTime = seconds;
    // TODO 00
    this->ticksRemaining = seconds * 60;
    this->secondsRemaining = seconds;
    this->timeElapsed = 0;
    this->isOver = false;
    return;
}

int timerObject::getTimeElapsed() {
    return this->timeElapsed;
}

int timerObject::getTotalTime() {
    return this->totalTime;
}

int timerObject::getSecondsRemaining() {
    return this->secondsRemaining;
}

// ----------

// ----- timeHandler -----

// Create a timerObject with a wait time of timeSeconds
class timerObject *timerHandler::createTimer() {
    class timerObject *ptrTimer = new class timerObject();
    this->allTimers.push_back(ptrTimer);
    this->numberOfTimers++;
    return ptrTimer;
}

void timerHandler::tickAll() {
    for (int x = 0; x < this->numberOfTimers; x++) {
        this->allTimers[x]->onTick();
    }
    return;
}

// ----------

