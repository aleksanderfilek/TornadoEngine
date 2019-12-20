#include"TE_main.h"
#include"TE_graphics.h"
#include<stdio.h>

int main(int argc, char *argv[]){
    TE_init("Tytul",640,640);
    Tex_Create("LogoFB.png",0,0,0);
    Tex_Create("LogoFB.png",320,0,0);
    Tex_Create("LogoFB.png",0,320,0);
    Tex_Create("LogoFB.png",320,320,0);
    Tex_draw();
    SDL_Delay(5000);
    Tex_free();
    TE_close();
    return 0;
}