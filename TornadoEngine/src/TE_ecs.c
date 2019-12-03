#include"TE_ecs.h"

void Ecs_Tex_add(Texture texture){
    textureElementNumber++;
    textureSystem = (Texture *)realloc(textureSystem,textureElementNumber*sizeof(Texture));
    textureSystem[textureElementNumber] = texture;
}

void Ecs_Tex_draw(){
    int i;
    for(i = 0; i < textureElementNumber; i++){
        Texture tex = textureSystem[i];
        SDL_RenderCopy(renderer,tex.texture,&tex.sourceRect,&tex.destinationRect);
    }
}

void Ecs_Tex_free(){
    free(textureSystem);
    textureElementNumber = 0;
}

void Ecs_Btn_add(Button button){
    buttonElementNumber++;
    buttonSystem = (Button *)realloc(buttonSystem,buttonElementNumber*sizeof(Button));
    buttonSystem[buttonElementNumber] = button;
}

void Ecs_Btn_update(int mousePosX, int mousePosY , Button *buttonStructs, int number){
    int i;
    Button button;
    for(i = 0; i < number; i++){
        button = buttonStructs[i];
        if(button.texture->destinationRect.x <= mousePosX && 
        button.texture->destinationRect.x + button.texture->destinationRect.w >= mousePosX &&
        button.texture->destinationRect.y <= mousePosY && 
        button.texture->destinationRect.y + button.texture->destinationRect.h >= mousePosY){
            if(!(button.state | hovered)){
                button.state = hovered;
                if(button.hover)button.hover();
            }
            if(e.type == SDL_MOUSEBUTTONDOWN){
                button.state = clicked;
                if(button.click)button.click();
            }
        }
        else if(button.state | hovered){
            button.state = none;
            if(button.unhover)button.unhover();
        }
    }
}

void Ecs_Btn_free(){
    free(buttonSystem);
    buttonElementNumber = 0;
}

void Ecs_clear(){
    Ecs_Btn_free();
    Ecs_Tex_free();
}