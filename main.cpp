#include"TE.h"
#include"TE_graphics.h"

class Game:public TornadoEngine{
private:
    Graphics graphics;
    Mesh mesh;
    Shader program;
protected:
    virtual void OnStart(){
        program.Load("vertex.vs","fragment.frag");
        mesh.LoadObj("Cube.obj");

        // vector3f vertices[3]{
        //     {-1.0f, 1.0f, 0.0f},
        //     {-1.0f, -1.0f, 0.0f},
        //     {1.0f, -1.0f, 0.0f}
        // };

        // vector2f uvs[3]{
        //     {0.0f,0.0f},
        //     {0.0f,0.0f},
        //     {0.0f,0.0f}
        // };

        // vector3ui indices[1]{
        //     {0, 1, 2}
        // };

        //mesh.Generate(vertices,3,uvs,3,indices,1);
        SetBackgroundColor(1.0f,0.0f,0.0f,1.0f);
    }

    virtual void OnUpdate(double elapsedTime){

    }

    virtual void OnDraw(){
        glUseProgram(program.ID);
        graphics.Draw(mesh);
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