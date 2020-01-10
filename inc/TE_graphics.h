#ifndef TEGRAPHICS_H_
#define TEGRAPHICS_H_

#include<fstream>
#include<string>
#include<sstream>
#include<iostream>
#include<vector>
#include<unordered_map>

#include<SDL.h>
#include<SDL_main.h>
#include<SDL_image.h>
#include<GL/glew.h>
#include<SDL_opengl.h>

#include<TE_math.h>

void Graphics_Init();
void Graphics_Close();


struct Shader{
    int ID;
    std::unordered_map<std::string,GLuint> uniformLocation;
};

Shader Shader_Load(const char *vertexSourcePath, const char *fragmentSourcePath);

class Material{
private:
    Shader programShader;
public:
    Material();
    ~Material();

    void Use();

    void BindTexture(int texture);
    void SetFloat(std::string uniformName, float value);
    void SetVector2(std::string uniformName, vector2 value);
    void SetVector3(std::string uniformName, vector3 value);
    void SetVector4(std::string uniformName, vector4 value);
    void SetMat2x2(std::string uniformName, mat2x2 value);
    void SetMat3x3(std::string uniformName, mat3x3 value);
    void SetMat4x4(std::string uniformName, mat4x4 value);
};

class Mesh{
    GLuint ID;
    vector3 *vertices;
    int *triangles;
    vector2 *uvs;
};

void CreateMesh(Mesh *mesh, vector3 *vertices, vector3 *triangles, vector3 *uvs);

void SetBackgroundColor(float r, float g, float b, float a);
#endif