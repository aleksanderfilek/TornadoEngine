#ifndef FONT_H_
#define FONT_H_

#include<SDL2/SDL_ttf.h>

struct Font{
    TTF_Font *font;
    int size;

    bool loadFont(const char *path, const int _size){
    bool success = true;
        font = TTF_OpenFont(path, _size);
        if(font == NULL){ success = false;}
        else {size = _size;}
        return success;
    }
};

#endif