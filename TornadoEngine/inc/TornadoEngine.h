#ifndef TORNADOENGINE_H_
#define TORNADOENGINE_H_

#include<stdio.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_main.h>
#include<SDL2/SDL_image.h>

class TornadoEngine{
private:
    SDL_Window *window;
    SDL_Point windowSize;
    SDL_Renderer *renderer;
public:
    //Constructor
    TornadoEngine();
    //Destructor
    ~TornadoEngine();
    //Initialize SDL
    bool init(const char *title, int width, int height, Uint32 flags);
    //Quit SDL
    void close();

    //Properties
    SDL_Window *getWindow(){return window;};
    SDL_Point getWindowSize(){return windowSize;};
    SDL_Renderer *getRenderer(){return renderer;};
};

#endif