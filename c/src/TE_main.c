#include"TE_main.h"

int TE_init(Engine *engine,const char *title, int width, int height){
    int success = 1;
    //Create window
    engine->window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if( engine->window == NULL )
    {
        printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
        success = 0;
    }
    else
    {
        engine->width = width;
        engine->height = height;
        //Create renderer for window
        engine->renderer = SDL_CreateRenderer( engine->window, -1, SDL_RENDERER_ACCELERATED );
        if( engine->renderer == NULL )
        {
            printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
            success = 0;
        }
        else
        {
            //Initialize renderer color
            SDL_SetRenderDrawColor( engine->renderer, 0xFF, 0xFF, 0xFF, 0xFF );

            //Initialize PNG loading
            int imgFlags = IMG_INIT_PNG;
            if( !( IMG_Init( imgFlags ) & imgFlags ) )
            {
                printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                success = 0;
            }
        }
    }
    return success;
}

void TE_close(Engine *engine){
    //Destroy window    
    SDL_DestroyRenderer( engine->renderer );
    SDL_DestroyWindow( engine->window );
    engine->window = NULL;
    engine->renderer = NULL;

    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}