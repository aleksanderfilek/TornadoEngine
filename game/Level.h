#ifndef LEVEL_H_
#define LEVEL_H_

#include"TE_graphics.h"
#include"TE_math.h"
#include"TE.h"

struct LevelElement{
    vector3f position;
    vector3f rotation;
    GLuint textureId;
};

class Level{
private:
    Mesh mesh;
    std::vector<Texture> texture;
    std::vector<LevelElement> elements;
public:
    Level(std::string path);
    ~Level();

    void Draw(Graphics &graphics, GLuint modelUniformLocation);
};

#endif