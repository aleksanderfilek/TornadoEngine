#include"TE.h"
#include"TE_graphics.h"

class Game:public TornadoEngine{
private:
    Graphics graphics;
    Mesh mesh;
    Shader program;
    mat4x4 model;
    float angle;
    GLuint modelLoc;
protected:
    virtual void OnStart(){
        program.Load("vertex.vs","fragment.frag");
        //mesh.LoadObj("Cube.obj");

        glUseProgram(program.ID);
        modelLoc = glGetUniformLocation(program.ID,"model");
        GLuint projectionLoc = glGetUniformLocation(program.ID,"projection");

        mat4x4 projection = {
            {0.769f,0.0f,0.0f,0.0f},
            {0.0f, 0.577f,0.0f,0.0f},
            {0.0f,0.0f,1.002f, 1.0f},
            {0.0f,0.0f,-0.2f,0.0f}
        };

        glUniformMatrix4fv(projectionLoc,1,GL_FALSE,&projection[0].x);

        vector3f vertices[]{ 
            {-1.0f, 1.0f, 1.0f},
            {1.0f, 1.0f, 1.0f},
            {-1.0f, -1.0f, 1.0f},

            {1.0f, 1.0f, 1.0f},
            {1.0f, -1.0f, 1.0f},
            {-1.0f, -1.0f, 1.0f},

            {-1.0f, 1.0f, -1.0f},
            {1.0f, 1.0f, -1.0f},
            {-1.0f, -1.0f, -1.0f},

            {1.0f, 1.0f, -1.0f},
            {1.0f, -1.0f, -1.0f},
            {-1.0f, -1.0f, -1.0f}
        };

        vector2f uvs[]{
            {1.0f,0.0f},
            {1.0f,0.0f},
            {1.0f,0.0f},

            {0.0f,1.0f},
            {0.0f,1.0f},
            {0.0f,1.0f},

            {0.5f,0.0f},
            {0.5f,0.0f},
            {0.5f,0.0f},

            {0.0f,0.5f},
            {0.0f,0.5f},
            {0.0f,0.5f}
        };

        vector3ui indices[]{
            {0, 1, 2},
            {3, 4, 5},
            {6, 7, 8},
            {9, 10, 11}
        };

        mesh.Generate(vertices,12,uvs,12,indices,4);
    }

    virtual void OnUpdate(double elapsedTime){
        angle += (float)elapsedTime;
                matrix_identity(model);
        matrix_scale(model,{0.2f,0.2f,0.2f});
        matrix_translate(model, {0.0f,2.0f,2.0f});
        matrix_rotate(model,{0.0f,0.0f,angle});
    }

    virtual void OnDraw(){

        glUniformMatrix4fv(modelLoc,1,GL_FALSE,&model[0].x);
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