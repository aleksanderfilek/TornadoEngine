#ifndef BUTTON_H_
#define BUTTON_H_

#include"Texture.h"
#include"Text.h"
#include"Mouse.h"
#include<SDL2/SDL.h>

class Button{
private:
    Texture *background;
    Text *text;

    bool isHovered = false;
    bool isClicked = false;

    bool hover(SDL_Point *point);
public:
    Button();
    ~Button();

    void draw(SDL_Renderer *renderer);
    void update(Mouse *mouse);

    bool IsHovered(){return isHovered;};
    bool IsClicked(){return isClicked;};

    Texture *GetBackground(){return background;};
    Text *GetText(){return text;};
};

#endif