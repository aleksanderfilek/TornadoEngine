#include"TE.h"
#include"TE_graphics.h"

class Game:public TornadoEngine{
private:

protected:
    virtual void OnStart(){
        Mesh mesh;
        mesh.LoadObj("Cube.obj");
    }

    virtual void OnUpdate(double elapsedTime){

    }

    virtual void OnDraw(){

    }

    virtual void OnExit(){
    }
};

int main(int argc, char **argv){
    Game game;
    game.CreateGame("Title",800,600);
    game.Start();
    return 0;
}