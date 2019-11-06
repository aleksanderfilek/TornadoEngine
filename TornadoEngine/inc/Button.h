#ifndef BUTTON_H_
#define BUTTON_H_

#include"Texture.h"
#include"Text.h"
#include"Component.h"

class Button: public Component{
private:
    Texture background;
    Text text;

    bool isHovered = false;
public:
    Button();
    virtual ~Button();

    virtual void draw(SDL_Renderer *renderer);
    virtual void update();

    void free();

    bool IsHovered(){return isHovered;};

    Texture *GetBackground(){return &background;};
    Text *GetText(){return &text;};
};

#endif