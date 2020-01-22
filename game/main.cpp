#include"TE.h"
#include"TE_graphics.h"

#include"Player.h"
#include"Level.h"

class Game:public TornadoEngine{
private:
    Graphics graphics;
    Shader program;
    GLuint modelLoc;
    mat4x4 lookAt;
    GLuint lookLoc;

    Player player;

    vector3f up = {0.0f, 1.0f, 0.0f};

    Level *level;

protected:
    virtual void OnStart(){        
        program.Load("res/vertex.vs","res/fragment.frag");

        glUseProgram(program.ID);
        modelLoc = glGetUniformLocation(program.ID,"model");
        GLuint projectionLoc = glGetUniformLocation(program.ID,"projection");

        mat4x4 projection;
        matrix_projection(projection,800,600,120.0f,0.1f,1000.0f);

        glUniformMatrix4fv(projectionLoc,1,GL_FALSE,&projection[0].x);

        lookLoc = glGetUniformLocation(program.ID,"lookAt");

        level = new Level("res/Level.bmp");
    }

    virtual void OnUpdate(float elapsedTime){
        vector3f eye, forward;
        player.Update(elapsedTime, eye ,forward);

        vector3f target = {0.0f,0.0f,0.0f};
        target = eye + forward;
        matrix_lookAt(lookAt,eye,target,up);
    }
    virtual void OnDraw(){
        glUniformMatrix4fv(lookLoc,1,GL_FALSE,&lookAt[0].x);

        level->Draw(graphics, modelLoc);
    }

    virtual void OnExit(){
        delete level;
    }
};

int main(int argc, char **argv){
    Game game;
    game.CreateGame("Title",800,600);
    game.Start();
    return 0;
}