#ifndef H_TIME
#define H_TIME
#include <chrono>
#include <cstdlib>
#include <vector>
#include <string>
#include <iostream>

// Todo list:
//
// 00 - Actually free all objects

class timerObject {
private:
    bool isOver;
    int secondsRemaining;
    int ticksRemaining;
    int totalTime;
    int timeElapsed;

public:
    timerObject() {
        this->totalTime = 0;
        this->ticksRemaining = 0;
        this->secondsRemaining = 0;
        this->timeElapsed = 0;
        this->isOver = true;
    }
    ~timerObject() {
        ;;
    }

    void onTick();

    // Setters
    void setTimer(int seconds);

    // Getters
    int getTimeElapsed();
    int getTotalTime();
    int getSecondsRemaining();

    bool isTimerDone();
};

class timerHandler {
private:
    int deltaTime;
    int numberOfTimers;
    std::vector<class timerObject *> allTimers;

public:
    timerHandler() {
        this->deltaTime = 0;
        this->numberOfTimers = 0;
    }
    ~timerHandler() {
        // Free all timer objects
        for (int x = 0; x < numberOfTimers; x++) {
            // TODO 00
            //delete allTimers[x];
        }
    }

    // Getters
    int getDeltaTime();

    // Setters

    // Methods
    void tickAll();
    class timerObject *createTimer();
    
};

#endif
