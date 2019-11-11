#include<stdio.h>

#include"TornadoEngine.h"

int main(){
    TornadoEngine engine;
    engine.init("Test",640,480,SDL_WINDOW_SHOWN);

    SDL_Delay(3000);

    engine.close();
}  