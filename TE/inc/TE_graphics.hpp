#ifndef TEGRAPHICS_H_
#define TEGRAPHICS_H_

#include<fstream>
#include<string>
#include<sstream>
#include<iostream>
#include<vector>
#include<unordered_map>
#include<stdlib.h>
#include<cstring>

#include<SDL.h>
#include<SDL_main.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<GL/glew.h>
#include<SDL_opengl.h>

#include"TE_math.hpp"

struct Texture{
    GLuint id;
    vector2ui size;
};

Texture Tex_Load(const char *path);
//TODO: function to set texture in GPU
void BindTexture(GLuint &index,const Texture &texture);

class Shader{
public:
    GLuint ID;
    std::unordered_map<std::string,GLuint> uniformLocation;
    //TODO: add uniform searching and combine shaders to one file
    void Load(const char *vertexSourcePath, const char *fragmentSourcePath);
};

struct vertex{
    vector3f position;
    vector2f uv;
};

class Mesh{
private:
    GLuint VAO, VBO, EBO;
    GLuint indicesCount;
public: 
    Mesh();
    ~Mesh();

    void Generate(vector3f *_vertices,unsigned int _verticesCount , vector2f *_uvs, unsigned int _uvsCount, vector3ui *_indices, unsigned int _indicesCount);
    bool LoadObj(std::string path);

    void Generate();
    GLuint GetId(){return VAO;};
    GLuint GetIndicesCount(){return indicesCount;};
};

class Graphics{
    public:
        Graphics();
        ~Graphics();

        void InstantiateMesh(Mesh &mesh);
        void DeinstantiateMesh();
        void DrawInstantiatedMesh();

        void Draw(Mesh &mesh);
};

void SetBackgroundColor(float r, float g, float b, float a);

typedef TTF_Font Font;
#endif