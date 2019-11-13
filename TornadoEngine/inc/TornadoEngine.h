#ifndef TORNADOENGINE_H_
#define TORNADOENGINE_H_

#include<stdio.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_main.h>
#include<SDL2/SDL_image.h>

#include"Button.h"
#include"Font.h"
#include"Mouse.h"
#include"State.h"
#include"Texture.h"
#include"Text.h"

enum class Keyboard{
    Num0 = 0,
};

class TornadoEngine{
private:
    SDL_Window *window;
    SDL_Point windowSize;
    SDL_Renderer *renderer;

    SDL_Event event;

    Uint8 *keyboardState;
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

    //check if key is pressed
    bool getKeyboardState(int key){return keyboardState[key];};

    //Properties
    SDL_Window *getWindow(){return window;};
    SDL_Point getWindowSize(){return windowSize;};
    SDL_Renderer *getRenderer(){return renderer;};
};

#endif