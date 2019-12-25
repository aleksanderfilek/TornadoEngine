#include"TE_main.h"
#include"TE_graphics.h"
#include<stdio.h>
#include<stdbool.h>

extern SDL_Renderer *renderer;
extern SDL_Event event;

void dodaj(int *num){
    (*num)++;
    Tex_create("Obrazek.png",((*num)%640)*2,0,0);
}

int main(int argc, char *argv[]){
    TE_init("Tytul",640,640);

    int num = 0;
    dodaj(&num);

    Timer Time;
    startTimer(&Time);
    double timer = 0;
    double deltaTime = 0;

    bool quit = false;
    while(!quit){
        while( SDL_PollEvent( &event ) != 0 )
        {
            if( event.type == SDL_QUIT )
            {
                quit = true;
            }
        }
        timer += deltaTime;

        if(timer >= .1f){
            timer -= .1f;
            dodaj(&num);
            printf("num = %d, fps = %f\n", num, 60/deltaTime);
        }
/*
        int i;
        for(i = 0; i < num; i++){
            //Tex_move(i,0,(int)(250*deltaTime));
        }
*/
        SDL_RenderClear(renderer);
        Tex_draw();
        SDL_RenderPresent(renderer);

        deltaTime = (double)restartTimer(&Time)/1000.f;
    }
    Tex_free();
    TE_close();
    return 0;
}