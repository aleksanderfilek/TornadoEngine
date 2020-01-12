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

        GLfloat vertices[] = {
        -0.5f, -0.5f, 0.0f, // Left  
         0.5f, -0.5f, 0.0f, // Right 
         0.0f,  0.5f, 0.0f,  // Top   
        };

        int indices[]{
            0, 1, 2
        };

        mesh.SetVertices(vertices,18);
        mesh.SetIndices(indices, 3);
        mesh.Generate();
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
    game.CreateGame("Title",640,480);
    game.Start();
    return 0;
}