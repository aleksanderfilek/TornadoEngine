#include"TE_main.h"

int main(int argc, char *argv[]){
    TE_init("Tytul",640,480);
    Tex_Create("LogoFB.png",10,10,0);
    Tex_draw();
    SDL_Delay(3000);
    Tex_free();
    TE_close();
    return 0;
}