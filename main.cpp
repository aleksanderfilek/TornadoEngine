#include"TE.h"
#include"TE_graphics.h"
#include<time.h>

#define N 100000

    vector3 positions[N];


float randMToN(float M, float A)
{
    return M + (rand() / ( RAND_MAX / (A-M) ) ) ;  
}

class Game:public TornadoEngine{
private:
    Graphics graphics;
    Mesh mesh;
    Shader program;
    GLuint translationLoc;
    int frames = 0;
    float timer;
protected:
    virtual void OnStart(){
        srand(time(NULL));

        program.Load("vertex.vs","fragment.frag");
        glUseProgram(program.ID);
        translationLoc = glGetUniformLocation(program.ID,"translation");

        GLfloat vertices[] = {
            0.5f, 0.5f, 0.0f, 
            0.5f, -0.5f, 0.0f,
            -0.5f, -0.5f, 0.0f,  
            -0.5f,  0.5f, 0.0f
        };

        int indices[]{
            0, 1, 3,
            1, 2, 3
        };

        mesh.SetVertices(vertices,12);
        mesh.SetIndices(indices, 6);
        mesh.Generate();

        for(int i = 0;i < N; i++){
            positions[i].x = randMToN(-15,15);
            positions[i].y = randMToN(-15,15);
            positions[i].z = randMToN(-15,15);
        }
    }

    virtual void OnUpdate(double elapsedTime){
        if(timer >= 1.0f){
            std::cout<<frames<<std::endl;
            frames = 0;
            timer = 0.0f;
        }

        frames++;

        timer += elapsedTime;
    }

    virtual void OnDraw(){
        graphics.InstantiateMesh(mesh);
        for(int i = 0;i < N; i++){
            glUniform3f(translationLoc,positions[i].x,positions[i].y,positions[i].z);
            graphics.DrawInstantiatedMesh();
        }
        graphics.DeinstantiateMesh();
    }

    virtual void OnExit(){
    }
};

int main(int argc, char **argv){
    Game game;
    game.CreateGame("Title",1000,800);
    game.Start();
    return 0;
}