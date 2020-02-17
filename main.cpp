#include"TE.hpp"

class Game:public TornadoEngine\
{
    protected:
        virtual void OnStart(){

        }

        virtual void OnUpdate(float elapsedTime){
            if(mouseButtonPressed(Left))
                printf("Left pressed\n");
            else if(mouseButtonUp(Left))
                printf("Left up\n");
            else if(mouseButtonDown(Left))
                printf("Left down\n");

            if(mouseButtonDown(Right))
                printf("right down\n");

            if(mouseButtonUp(Right))
                printf("right up\n");

            if(keyPressed(A))
                printf("A pressed\n");
            else if(keyUp(A))
                printf("A up\n");
            else if(keyDown(A))
                printf("A down\n");
        }

        virtual void OnDraw(){

        }

        virtual void OnExit(){

        }
};


int main(int argv, char *argc[]){
    Game game;
    game.CreateGame("Test",640,480);
    game.Start();
    return 0;
}