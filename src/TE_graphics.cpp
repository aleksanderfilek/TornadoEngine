#include"TE_graphics.h"

const GLfloat vertices[]{
    0.0f, 0.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 1.0f, 0.0f,
    1.0f, -1.0f, 1.0f, 1.0f,
    1.0f, -1.0f, 1.0f, 1.0f,
    0.0f, -1.0f, 0.0f, 1.0f,
    0.0f,0.0f, 0.0f, 0.0f
};

GLuint VAO, VBO, EBO;

void Graphics_Init(){
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    glBindVertexArray(0); 
}

void Graphics_Close(){
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

shader Shader_Load(const char *vertexSourcePath, const char *fragmentSourcePath){
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try{
        vShaderFile.open(vertexSourcePath);
        fShaderFile.open(fragmentSourcePath);
        std::stringstream vShaderStream, fShaderStream;

        vShaderStream<<vShaderFile.rdbuf();
        fShaderStream<<fShaderFile.rdbuf();

        vShaderFile.close();
        fShaderFile.close();

        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch(std::ifstream::failure e){
        std::cout<<"ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ"<<std::endl;
    }

    const GLchar *vShaderCode = vertexCode.c_str();
    const GLchar *fShaderCode = fragmentCode.c_str();

    GLchar vertex, fragment;

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);

    GLuint program = glCreateProgram();
    glAttachShader(program,vertex);
    glAttachShader(program,fragment);
    glLinkProgram(program);

    glDeleteShader(vertex);
    glDeleteShader(fragment);

    return program;
}

Texture Tex_Load(const char *path){
    SDL_Surface *surface = IMG_Load(path);
    if(surface == NULL){
        std::cout<<"Texture could not be load"<<std::endl;
    }
    else{
        GLuint texId;
        glGenTextures(1, &texId);
        glBindTexture(GL_TEXTURE_2D, texId);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, surface->w, surface->h, 0, GL_RGB, GL_UNSIGNED_BYTE, surface->pixels);
        glGenerateMipmap(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);

        int w = surface->w;
        int h = surface->h;

        SDL_FreeSurface(surface);
        vector2 vec;
        vec.x = w;
        vec.y = h;
        return {texId,vec};
    }
    vector2 vec;
    return {0,vec};
}

void Tex_Draw(Texture *texture, shader Shader, vector2 position){
    glBindTexture(GL_TEXTURE_2D, texture->id);
    
    GLuint posLoc = glGetUniformLocation(Shader,"position");
    glUniform2f(posLoc,position.x,position.y);
    GLuint sizeLoc = glGetUniformLocation(Shader,"size");
    glUniform2f(sizeLoc,64.0f,64.0f);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void Tex_DrawEx(Texture *texture, shader Shader, vector2 position, vector2 scale, vector4 srcRect){
    glBindTexture(GL_TEXTURE_2D, texture->id);
    
    GLuint posLoc = glGetUniformLocation(Shader,"position");
    glUniform2f(posLoc,position.x,position.y);
    GLuint sizeLoc = glGetUniformLocation(Shader,"size");
    float w= texture->size.x * scale.x;
    float h = texture->size.y * scale.y;
    glUniform2f(sizeLoc,w,h);
    GLuint srcRectLoc = glGetUniformLocation(Shader,"srcRect");
    glUniform4f(srcRectLoc,srcRect.x,srcRect.y,srcRect.z,srcRect.w);
    
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void SetBackgroundColor(float r, float g, float b, float a){
    glClearColor(r,g,b,a);
}
