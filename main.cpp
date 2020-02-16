#include"TE.hpp"

class Game:public TornadoEngine\
{
    protected:
        virtual void OnStart(){

        }

        virtual void OnUpdate(float elapsedTime){

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