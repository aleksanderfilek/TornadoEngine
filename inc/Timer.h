#ifndef TIMER_H_
#define TIMER_H_

#include<SDL2/SDL.h>

class Timer{
 public:
        //Initializes variables
        Timer();

        //The various clock actions
        void start();
        void stop();
        Uint32 restart();

        //Checks the status of the timer
        bool isStarted();

    private:
        //The clock time when the timer started
        Uint32 mStartTicks;

        bool mStarted;
};
#endif