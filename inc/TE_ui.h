#ifndef TEUI_H_
#define TEUI_H_

#include"TE_graphics.h"

enum Alligment{LeftCenter, Center};

class Text{
private:
    Texture texture;
    Alligment textAlligment;
    int fontId;
    vector2 position;
    vector2 size;
    vector2 scale;
public:
    Text();
    ~Text();

    void Draw();
    void SetText(const char *text);
};

#endif