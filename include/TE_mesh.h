#ifndef TEMESH_H_
#define TEMESH_H_

#include"TE.h"

typedef struct{
    float3 position;
    float3 normal;
    float2 texture_coord;
}TE_Vertex;

void TE_vertex_set(TE_Vertex* vertex, float3 _position, 
                    float3 _normal, float2 _texture_coord);

typedef struct{
    unsigned int VAO, VBO, EBO;

    TE_Vertex* vertices;
    unsigned int vertices_count;

    unsigned int* indices;
    unsigned int indices_count;
}TE_Mesh;

TE_Mesh* TE_mesh_create();
int TE_mesh_load(TE_Mesh* mesh, const char* path);
void TE_mesh_set(TE_Mesh* mesh, TE_Vertex* _vertices, unsigned int _vertices_count, 
                unsigned int* _indices, unsigned int _indices_count);
void TE_mesh_clear(TE_Mesh* mesh);

void TE_mesh_draw(const TE_Mesh* mesh);
void TE_mesh_draw_instanced(const TE_Mesh* mesh, unsigned int count);

#endif