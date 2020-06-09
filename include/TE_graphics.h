#ifndef TEGRAPHICS_H_
#define TEGRAPHICS_H_

#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_ttf.h>

#include<GL/glew.h>

#include<SDL2/SDL_opengl.h>
#include<SOIL/SOIL.h>

#include"TE_math.h"
#include"TE_core.h"

#include<vector>
#include<fstream>
#include<string>
#include<sstream>
#include<map>
#include<string.h>

int Clear();
int SetDrawColor(uint8_t R, uint8_t G, uint8_t B, uint8_t A);
void Render();

struct Texture{
    unsigned int id;
    int width, height;
};

class TextureManager{
    private:
        std::map<std::string, unsigned int> textures_organizer;
        std::vector<Texture> textures;
    public:
        ~TextureManager();
        unsigned int LoadTexture(std::string path);
        void DestroyTexture(unsigned int textureID);
        void Bind(unsigned int count, unsigned int *textureID);
        void GetTextureSize(unsigned int textureID, int *width, int *height);
        bool GetTextureID(std::string textureName, unsigned int *id);
};

struct Vertex{
    float3 position;
    float3 normal;
    float2 textureCoord;
};

class Mesh{
    private:
        unsigned int VAO, VBO, EBO;

        unsigned int *textures;
        unsigned int texturesCount;

        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        void setupMesh();
    public:
        Mesh(){};
        Mesh(std::vector<Vertex> _vertices, std::vector<unsigned int> _indices, bool saveData);
        ~Mesh();

        bool Load(std::string path);     
        void Set(std::vector<Vertex> _vertices, std::vector<unsigned int> _indices, bool saveData);   
        void SetTextures(unsigned int count, unsigned int *_textures);
        void Clear(bool onlyData);

        friend void Draw(const Mesh& mesh);
        friend void DrawInstanced(int count, const Mesh& mesh);
};

void Draw(const Mesh& mesh);
void DrawInstanced(int count, const Mesh& mesh);

class Shader{
private:
    unsigned int ID;
    std::map<std::string, unsigned int> uniform_Loc;
public:
    void Load(std::string path);
    void Bind();
    inline unsigned int GetUniformLoc(std::string name){
        return uniform_Loc[name];
    }
};


#endif