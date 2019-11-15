#include"Timer.h"

void Timer::start(){
    this->mStarted = true;
    this->mStartTicks = SDL_GetTicks();
}

void Timer::stop(){
    this->mStarted = false;
    this->mStartTicks = 0;
}

Uint32 Timer::restart(){
    Uint32 time = SDL_GetTicks() - this->mStartTicks;
    stop();
    start();
    return time;
}

