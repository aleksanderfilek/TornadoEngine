#ifndef TEXT_H_
#define TEXT_H_

#include<SDL2/SDL.h>
#include<SDL2/SDL_ttf.h>

#include"Texture.h"

class Text: public Texture{
private:
    TTF_Font *font;
    char *text;
public:
    Text();
    ~Text();

    bool setFont(const char *path, int size);
    static TTF_Font *loadFont(const char *path, int size){return TTF_OpenFont(path, size);};

    char *getText(){return text;};
    void setText(char *_text);
};

#endif