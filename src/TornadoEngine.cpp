#include"TornadoEngine.h"

TornadoEngine::TornadoEngine(){

}

TornadoEngine::~TornadoEngine(){
    
}

bool TornadoEngine::init(const char *title, int width, int height, Uint32 flags){
    bool success = true;
    //Create window
    this->window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags);
    if( this->window == NULL )
    {
        printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        windowSize = {width, height};
        //Create renderer for window
        this->renderer = SDL_CreateRenderer( this->window, -1, SDL_RENDERER_ACCELERATED );
        if( this->renderer == NULL )
        {
            printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            //Initialize renderer color
            SDL_SetRenderDrawColor( this->renderer, 0xFF, 0xFF, 0xFF, 0xFF );

            //Initialize PNG loading
            int imgFlags = IMG_INIT_PNG;
            if( !( IMG_Init( imgFlags ) & imgFlags ) )
            {
                printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                success = false;
            }
        }
    }
    return success;
}

void TornadoEngine::close(){
    //Destroy window    
    SDL_DestroyRenderer( this->renderer );
    SDL_DestroyWindow( this->window );
    this->window = NULL;
    this->renderer = NULL;

    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}

void TornadoEngine::EventUpdate(){
    //this->keyboardState = SDL_GetKeyboardState(NULL);
}