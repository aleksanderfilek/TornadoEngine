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

        mat4x4 projection;
        matrix_projection(projection,800,600,120.0f,0.1f,100.0f);
        for(int i = 0;i < 4; i++)
            std::cout<<projection[i].x<<"  "<<projection[i].y<<"  "<<projection[i].z<<"  "<<projection[i].w<<std::endl;

        glUniformMatrix4fv(projectionLoc,1,GL_FALSE,&projection[0].x);

        vector3f vertices[]{ 
            //FRONT
            {-1.0f, 1.0f, 1.0f},
            {1.0f, 1.0f, 1.0f},
            {-1.0f, -1.0f, 1.0f},

            {1.0f, 1.0f, 1.0f},
            {1.0f, -1.0f, 1.0f},
            {-1.0f, -1.0f, 1.0f},

            //BACK
            {-1.0f, 1.0f, -1.0f},
            {1.0f, 1.0f, -1.0f},
            {-1.0f, -1.0f, -1.0f},

            {1.0f, 1.0f, -1.0f},
            {1.0f, -1.0f, -1.0f},
            {-1.0f, -1.0f, -1.0f},

            //TOP
            {-1.0f, 1.0f, 1.0f},
            {1.0f, 1.0f, -1.0f},
            {1.0f, 1.0f, 1.0f},
        
            {-1.0f, 1.0f, 1.0f},
            {-1.0f, 1.0f, -1.0f},
            {1.0f, 1.0f, -1.0f},
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
            {0.0f,0.5f},

            
            {0.25f,0.25f},
            {0.25f,0.25f},
            {0.25f,0.25f},

            {0.5f,0.5f},
            {0.5f,0.5f},
            {0.5f,0.5f}
        };

        vector3ui indices[]{
            {0, 1, 2},
            {3, 4, 5},
            {6, 7, 8},
            {9, 10, 11},
            {12, 13, 14},
            {15, 16, 17}
        };

        mesh.Generate(vertices,18,uvs,18,indices,6);
  
    }

    virtual void OnUpdate(double elapsedTime){
        angle += (float)elapsedTime;
        matrix_identity(model);
        matrix_scale(model,{0.2f,0.2f,0.2f});
        matrix_rotate(model,{angle,angle*2.0f,angle*3.0f});
        matrix_translate(model, {0.0f,0.0f,3.0f});
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