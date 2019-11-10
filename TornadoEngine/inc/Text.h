#ifndef TEXT_H_
#define TEXT_H_

#include<SDL2/SDL.h>
#include"Font.h"

#include"Texture.h"

class Text: public Texture{
private:
    Font font;
    char *text;
public:
    Text();
    ~Text();

    bool setFont(const char *path, int size);
    static TTF_Font *loadFont(const char *path, int size){return TTF_OpenFont(path, size);};

    char *getText(){return text;};
    void setText(const char *_text);
};

#endif