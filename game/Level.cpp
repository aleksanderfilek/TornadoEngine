#include"Level.h"

Level::Level(std::string path){
    vector3f vertices[]{
        {-1.0f, -1.0f, 0.0f},
        {1.0f, 1.0f, 0.0f},
        {1.0f, -1.0f, 0.0f},
        {-1.0f, 1.0f, 0.0f}
    };

    vector2f uvs[]{
        {0.0f, 0.0f},
        {1.0f, 1.0f},
        {1.0f, 0.0f},
        {0.0f, 1.0f}
    };

    vector3ui indices[]{
        {0,1,2},
        {0,3,1}
    };

    this->mesh.Generate(vertices,4,uvs,4,indices,2);

}

Level::~Level(){

}

void Level::Draw(Graphics &graphics, GLuint modelUniformLocation){
    graphics.InstantiateMesh(this->mesh);
    graphics.DrawInstantiatedMesh();
    graphics.DeinstantiateMesh();
}