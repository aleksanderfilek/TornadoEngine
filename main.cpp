#include"TE.hpp"

class Game:public TornadoEngine\
{
    protected:
        virtual void OnStart(){

        }

        virtual void OnUpdate(float elapsedTime){
            if(mouseButtonDown(Left))
                printf("Left down\n");
            else if(mouseButtonUp(Left))
                printf("Left up\n");
            else if(mouseButtonPressed(Left))
                printf("Left presses\n");

            if(mouseButtonDown(Right))
                printf("Right down\n");
            else if(mouseButtonUp(Right))
                printf("Right up\n");
            else if(mouseButtonPressed(Right))
                printf("Right presses\n");

            if(mouseButtonDown(Middle))
                printf("Middle down\n");
            else if(mouseButtonUp(Middle))
                printf("Middle up\n");
            else if(mouseButtonPressed(Middle))
                printf("Middle presses\n");

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