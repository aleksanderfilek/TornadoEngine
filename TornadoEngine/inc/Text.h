#ifndef TEXT_H_
#define TEXT_H_

#include<SDL2/SDL.h>
#include"Font.h"

#include"Texture.h"
#include"Component.h"

class Text: public Texture,public Component{
private:
    Font font;
    char *text;
    SDL_Color color;
public:
    Text(char *_text, const char *path, int size, SDL_Renderer *renderer);
    ~Text();

    bool setFont(const char *path, int size, SDL_Renderer *renderer);

    char *getText(){return text;};
    bool setText(const char *_text, SDL_Renderer *renderer);

    void update();
    void draw(SDL_Renderer *renderer);
};

#endif