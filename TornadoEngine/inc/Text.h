#ifndef TEXT_H_
#define TEXT_H_

#include<SDL2/SDL.h>
#include"Font.h"

#include"Texture.h"

class Text: public Texture{
private:
    Font font;
    char *text;
    SDL_Color color;
public:
    Text(char *_text, const char *path, int size);
    ~Text();

    bool setFont(const char *path, int size);

    char *getText(){return text;};
    bool setText(const char *_text, SDL_Renderer *renderer);
};

#endif