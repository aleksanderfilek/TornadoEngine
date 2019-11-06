#ifndef TORNADOENGINE_H_
#define TORNADOENGINE_H_

#include<SDL2/SDL.h>
#include<SDL2/SDL_main.h>

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
    bool init(const char *title, int width, int height);
    //Quit SDL
    void close();

    //Properties
    SDL_Window *getWindow(){return window;};
    SDL_Point getWindowSize(){return windowSize;};
    SDL_Renderer *getRenderer(){return renderer;};
};

#endif