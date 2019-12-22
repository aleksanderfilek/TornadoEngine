#include"TE_main.h"
#include"TE_graphics.h"
#include<stdio.h>
#include<stdbool.h>

extern SDL_Event event;

int main(int argc, char *argv[]){
    TE_init("Tytul",640,640);

    Texture *tex = Tex_Create("LogoFB.png",0,0,0);
    Timer timer;

    float sx = 0;
    float sy = 0;

    bool quit = false;
    while(!quit){
         while( SDL_PollEvent( &event ) != 0 )
        {
            if( event.type == SDL_QUIT )
            {
                quit = true;
            }
        }
        float time = restartTimer(&timer)/ 1000.0f;
        sx += time;
        sy += time;
        sx = (sx>2)?0:sx;
        sy = (sy>2)?0:sy;
        Tex_setScale(tex,sx,sy);
        Tex_draw();
    }
    Tex_free();
    TE_close();
    return 0;
}