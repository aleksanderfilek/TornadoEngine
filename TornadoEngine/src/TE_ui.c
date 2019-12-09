#include"TE_ui.h"

Button *Btn_init(TTF_Font *font, const char *text, SDL_Texture *backgroundTexture, int posX, int posY, float scaleX, float scaleY){
    Button button;

    Tex_setTexture(button.texture,backgroundTexture);
    Tex_setPosition(button.texture,posX, posY);
    Tex_setScale(button.texture,scaleX,scaleY);

    button.text->font = font;
    Text_setText(button.text,text);
    Tex_setPosition(button.text->texture,posX,posY);
    Tex_setScale(button.text->texture,scaleX,scaleY);

    return Ecs_Btn_add(&button);
}