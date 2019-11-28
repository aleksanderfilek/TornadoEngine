#ifndef MOUSE_H_
#define MOUSE_H_

#include<SDL2/SDL.h>
#include"Texture.h"

class Mouse{
    public:
        Mouse(const char* cursorPath, SDL_Renderer *renderer);
        ~Mouse();
        SDL_Point *getMousePosition();
        void render(SDL_Renderer *renderer);
        bool getMouseDown(){return clicked;};
        void update(const SDL_Event *e);
    private:
        Texture texture;
        bool clicked = false;
};

#endif