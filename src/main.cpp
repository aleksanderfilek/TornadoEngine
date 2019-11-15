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
    int x=0,y=0;

    Timer timer;
    timer.start();
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
                switch(e.key.keysym.sym){
                    case SDLK_UP:
                        y = -5;
                        break;
                    case SDLK_DOWN:
                        y = 5;
                        break;
                    case SDLK_LEFT:
                        x = -5;
                        break;
                    case SDLK_RIGHT:
                        x = 5;
                        break;
                }
            }  

            if( e.type == SDL_KEYUP )
            {
                switch(e.key.keysym.sym){
                    case SDLK_UP:
                        y = 0;
                        break;
                    case SDLK_DOWN:
                        y = 0;
                        break;
                    case SDLK_LEFT:
                        x = 0;
                        break;
                    case SDLK_RIGHT:
                        x = 0;
                        break;
                }
            }        
        }
        :
        float deltaTime = timer.restart() / 1000.f;
        texture.move(x * deltaTime,y * deltaTime);
        SDL_RenderClear(renderer);
        texture.render(renderer);
        SDL_RenderPresent(renderer);

    }


    engine.close();
}  