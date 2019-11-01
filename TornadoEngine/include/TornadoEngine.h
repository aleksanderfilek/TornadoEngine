#ifndef TORNADOENGINE_DLL_H
#define TORNADOENGINE_DLL_H

#ifdef TORNADOENGINE_DLL
#define TORNADOENGINE_API __declspec(dllexport)
#else
#define TORNADOENGINE_API __declspec(dllimport)
#endif

#include<SDL.h>
#include<SDL_main.h>
#include<SDL_image.h>

class TornadoEngine{
private:
    SDL_Window *window;
    SDL_Renderer *renderer;    
public:
    TornadoEngine();
    ~TornadoEngine();
    bool init(const char *title,int width, int height, Uint32 flags);
    void close();

    SDL_Window *getWindow(){return window;};
    SDL_Renderer *getRenderer(){return renderer;};
};


#endif