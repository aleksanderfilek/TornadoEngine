#include"TE_ecs.h"

void Ecs_Tex_draw(SDL_Renderer *renderer,const Texture *textureStructs, int number){
    int i;
    for(i = 0; i < number; i++){
        Texture tex = textureStructs[i];
        SDL_RenderCopy(renderer,tex.texture,&tex.sourceRect,&tex.destinationRect);
    }
}