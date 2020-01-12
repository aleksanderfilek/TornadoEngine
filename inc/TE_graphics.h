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
#include<GL/glew.h>
#include<SDL_opengl.h>

#include<TE_math.h>

struct Texture{
    GLuint id;
    vector2 size;
};

Texture Tex_Load(const char *path);

class Shader{
public:
    GLuint ID;
    std::unordered_map<std::string,GLuint> uniformLocation;
    //TODO: add uniform searching and combine shaders to one file
    void Load(const char *vertexSourcePath, const char *fragmentSourcePath);
};

//zapytać się czy taki czy w klasach
union value{
    float Float;
    vector2 Vector2;
    vector3 Vector3;
    vector4 Vector4;
    mat2x2 Mat2x2;
    mat3x3 Mat3x3;
    mat4x4 Mat4x4;
};

struct MaterialProperty{
    GLuint location;
    int type;
    value Value;
};

class Material{
private:
    Shader programShader;
    std::vector<MaterialProperty> property;
    Texture texture;
public:
    Material();
    ~Material();

    void Use();

    void BindTexture(Texture texture, bool Static);
    void SetFloat(std::string uniformName, float value, bool Static);
    void SetVector2(std::string uniformName, vector2 value, bool Static);
    void SetVector3(std::string uniformName, vector3 value, bool Static);
    void SetVector4(std::string uniformName, vector4 value, bool Static);
    void SetMat2x2(std::string uniformName, mat2x2 value, bool Static);
    void SetMat3x3(std::string uniformName, mat3x3 value, bool Static);
    void SetMat4x4(std::string uniformName, mat4x4 value, bool Static);
};

class Mesh{
private:
    GLuint VAO,VBO, EBO;
    GLuint verticesCount;
    GLuint indicesCount;
    GLuint uvsCount;
    float *vertices;
    int *indices;
    float *uvs;
public: 
    Mesh();
    ~Mesh();

    void SetVertices(float *_vertices, unsigned int count);
    void SetIndices(int *_indices, unsigned int count);
    void SetUvs(float *_uvs, unsigned int count);
    
    void GetVertices(float *_vertices, unsigned int *count);
    void GetIndices(float *_indices, unsigned int *count);
    void GetUvs(float *_uvs, unsigned int *count);

    void LoadObj(std::string path);

    void Generate();
    GLuint GetId(){return VAO;};
    GLuint GetVerticesCount(){return verticesCount;};
};

class Graphics{
    public:
        Graphics();
        ~Graphics();

        void Draw(Mesh &mesh);
};

void SetBackgroundColor(float r, float g, float b, float a);
#endif