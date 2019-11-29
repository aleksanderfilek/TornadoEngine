#ifndef TEMAIN_H_
#define TEMAIN_H_

#include<SDL2/SDL.h>
#include<SDL2/SDL_main.h>
#include<SDL2/SDL_image.h>

class TornadoEngine{
private:
    SDL_Window *window;
    SDL_Point windowSize;
    SDL_Renderer *renderer;

    SDL_Event event;
public:
    //Constructor
    TornadoEngine();
    //Destructor
    ~TornadoEngine();
    //Initialize SDL
    bool init(const char *title, int width, int height, Uint32 flags);
    //Quit SDL
    void close();

    //Event handling
    void EventUpdate();

    //Properties
    SDL_Window *getWindow(){return window;};
    SDL_Point getWindowSize(){return windowSize;};
    SDL_Renderer *getRenderer(){return renderer;};
};

class State{
public:
    State(){}
    virtual ~State() = 0;
    virtual int update() = 0;
    virtual void draw() = 0;
};

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