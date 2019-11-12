#include<stdio.h>

#include"TornadoEngine.h"

int main(){
    TornadoEngine engine;
    engine.init("Test",640,480,SDL_WINDOW_SHOWN);

    SDL_Renderer *renderer = engine.getRenderer();

    Texture texture;
    texture.setTexture("resources/Obrazek.png",renderer);

    SDL_Event e;
    bool quit = false;
    while( !quit )
    {
        //Handle events on queue
        while( SDL_PollEvent( &e ) != 0 )
        {
            //User requests quit
            if( e.type == SDL_QUIT )
            {
                quit = true;
            }
            else if( e.type == SDL_KEYDOWN )
            {
                //Select surfaces based on key press
                if(e.key.keysym.sym == SDLK_UP){
                    texture.move(0,-5);
                }else if(e.key.keysym.sym == SDLK_DOWN){
                    texture.move(0,5);
                }

                if(e.key.keysym.sym == SDLK_RIGHT){
                    texture.move(5,0);
                }else if(e.key.keysym.sym == SDLK_LEFT){
                    texture.move(-5,0);
                }
            }        
        }

        SDL_RenderClear(renderer);
        texture.render(renderer);
        SDL_RenderPresent(renderer);
    }


    engine.close();
}  