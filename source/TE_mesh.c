#include"TE_mesh.h"

void TE_vertex_set(TE_Vertex* vertex, float3 _position, 
                    float3 _normal, float2 _texture_coord)
{
    vertex->position = _position;
    vertex->normal = _normal;
    vertex->texture_coord = _texture_coord;
}

TE_Mesh* TE_mesh_create()
{
    TE_Mesh* mesh = calloc(1 ,sizeof(TE_Mesh));
    mesh->VAO = -1;
    return mesh;
}

static void setup_mesh(TE_Mesh* mesh)
{
    glGenVertexArrays(1, &mesh->VAO);
    glGenBuffers(1, &mesh->VBO);
    glGenBuffers(1, &mesh->EBO);

    glBindVertexArray(mesh->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, mesh->VBO);
    glBufferData(GL_ARRAY_BUFFER, mesh->vertices_count * sizeof(TE_Vertex), &mesh->vertices[0], GL_STATIC_DRAW);  

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->indices_count * sizeof(unsigned int), &mesh->indices[0], GL_STATIC_DRAW);


    glEnableVertexAttribArray(0);	
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(1);	
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3* sizeof(GLfloat)));
    glEnableVertexAttribArray(2);	
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));

    glBindVertexArray(0);

}

int TE_mesh_load(TE_Mesh* mesh, const char* path)
{
    unsigned int position_capacity = 21;
    unsigned int position_length = 0;
    float3* positions = (float3*)malloc(position_capacity * sizeof(float3));

    unsigned int normal_capacity = 21;
    unsigned int normal_length = 0;
    float3* normals = (float3*)malloc(normal_capacity * sizeof(float3));

    unsigned int texture_coord_capacity = 21;
    unsigned int texture_coord_length = 0;
    float2* texture_coords = (float2*)malloc(texture_coord_capacity * sizeof(float2));

    unsigned int vertices_capacity = 21;
    unsigned int vertices_length = 0;
    TE_Vertex* vertices = (TE_Vertex*)malloc(vertices_capacity * sizeof(TE_Vertex));

    unsigned int indices_capacity = 21;
    unsigned int indices_length = 0;
    unsigned int* indices = (unsigned int*)malloc(indices_capacity * sizeof(unsigned int));

    FILE *file = fopen(path,"r");
    if(file == NULL)
    {
        printf("Imposible to open the file !\n");
        return -1;
    }

    while(1)
    {
        char lineHeader[128];
        int res = fscanf(file, "%s", lineHeader);
        if (res == EOF)
            break; 

        if(strcmp( lineHeader, "vt" ) == 0)
        {
            float2 uv;
            fscanf(file, "%f %f\n", &uv.x, &uv.y);
            texture_coords[texture_coord_length++] = uv;
            if(texture_coord_length == texture_coord_capacity)
            {
                texture_coord_capacity += 21;
                texture_coords = (float2*)realloc(texture_coords, texture_coord_capacity * sizeof(float2));
            }
        }
        else if(strcmp( lineHeader, "vn" ) == 0)
        {
            float3 normal;
            fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
            normals[normal_length++] = normal;
            if(normal_length == normal_capacity)
            {
                normal_capacity += 21;
                normals = (float3*)realloc(normals, normal_capacity * sizeof(float3));
            }
        }
        else if(strcmp( lineHeader, "v" ) == 0)
        {
            float3 position;
            fscanf(file, "%f %f %f\n", &position.x, &position.y, &position.z );
            positions[position_length++] = position;
            if(position_length == position_capacity)
            {
                position_capacity += 21;
                positions = (float3*)realloc(positions, position_capacity * sizeof(float3));
            }
        }
        else if(strcmp( lineHeader, "f" ) == 0){
            int f1, f2, f3, f4, f5, f6, f7, f8, f9;
            fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n",&f1,&f2,&f3,&f4,&f5,&f6,&f7,&f8,&f9);

            TE_Vertex v0,v1,v2;

            v0.position = positions[f1-1];
            v0.texture_coord = texture_coords[f2-1];
            v0.normal = normals[f3-1]; 

            v1.position = positions[f4-1];
            v1.texture_coord = texture_coords[f5-1];
            v1.normal = normals[f6-1]; 

            v2.position = positions[f7-1];
            v2.texture_coord = texture_coords[f8-1];
            v2.normal = normals[f9-1]; 

            vertices[vertices_length++] = v0;
            indices[indices_length++] = vertices_length - 1;
            vertices[vertices_length++] = v1;
            indices[indices_length++] = vertices_length - 1;
            vertices[vertices_length++] = v2;
            indices[indices_length++] = vertices_length - 1;

            if(vertices_length == vertices_capacity)
            {
                vertices_capacity += 21;
                vertices = (TE_Vertex*)realloc(vertices, vertices_capacity * sizeof(TE_Vertex));
            }

            if(indices_length == indices_capacity)
            {
                indices_capacity += 21;
                indices = (unsigned int*)realloc(indices, indices_capacity * sizeof(unsigned int));
            }
        }
    }


    fclose(file);

    free(positions);
    free(normals);
    free(texture_coords);

    TE_mesh_set(mesh, vertices, vertices_length, indices, indices_length);

    free(vertices);
    free(indices);

    return 0;
}

void TE_mesh_set(TE_Mesh* mesh, TE_Vertex* _vertices, unsigned int _vertices_count, 
                unsigned int* _indices, unsigned int _indices_count)
{
    if((mesh->VAO + 1) == 0){
        TE_mesh_clear(mesh);
    }

    mesh->vertices = (TE_Vertex*)malloc(_vertices_count * sizeof(TE_Vertex));
    mesh->vertices_count = _vertices_count;
    memcpy(mesh->vertices, _vertices, _vertices_count * sizeof(TE_Vertex));

    mesh->indices = (unsigned int*)malloc(_indices_count * sizeof(unsigned int));
    mesh->indices_count = _indices_count;
    memcpy(mesh->indices, _indices, _indices_count * sizeof(unsigned int));

    setup_mesh(mesh);
}

void TE_mesh_clear(TE_Mesh* mesh)
{

    free(mesh->vertices);
    mesh->vertices = NULL;
    mesh->vertices_count = 0;

    free(mesh->indices);
    mesh->indices = NULL;
    mesh->indices_count = 0;

    glDeleteVertexArrays(1, &mesh->VAO);
    glDeleteBuffers(1, &mesh->VBO);
    glDeleteBuffers(1, &mesh->EBO);

    mesh->VAO = -1;
}

void TE_mesh_draw(const TE_Mesh* mesh)
{
    glBindVertexArray(mesh->VAO);
    glDrawElements(GL_TRIANGLES, mesh->indices_count, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void TE_mesh_draw_instanced(const TE_Mesh* mesh, unsigned int count)
{
    glBindVertexArray(mesh->VAO);
    glDrawElementsInstanced(GL_TRIANGLES, mesh->indices_count, GL_UNSIGNED_INT, 0, count);
    glBindVertexArray(0);
}

TE_SharedMeshManager* TE_sharedMeshManager_init(int size)
{
    TE_SharedMeshManager* manager = (TE_SharedMeshManager*)malloc(sizeof(TE_SharedMeshManager));

    manager->allocated_elements = size;

    manager->name = (char**)malloc(size * sizeof(char*));
    manager->mesh = (TE_Mesh*)malloc(size * sizeof(TE_Mesh));

    return manager;
}

void TE_sharedMeshManager_free(TE_SharedMeshManager* manager)
{
    // free string and delete glTexture
    for(int i = 0; i < manager->allocated_elements; i++)
    {
        if(manager->name[i] != NULL)
        {
            free(manager->name[i]);
            TE_mesh_clear(&manager->mesh[i]);
        }
    }

    free(manager->name);
    free(manager->mesh);

    manager->allocated_elements = 0;

    free(manager);
}

TE_SharedMesh TE_sharedMeshManager_load(TE_SharedMeshManager* manager, const char* path)
{
    // check if mesh already was loaded. If yes, return index
    for(int i = 0; i < manager->allocated_elements; i++)
    {
        if(manager->name[i] != NULL && strcmp(path, manager->name[i]) == 0)
        {
            return i;
        }
    }

    TE_Mesh mesh;
    if(TE_mesh_load(&mesh, path) < 0)
    {
        return -1;
    }

        // find space for new mesh
    int index;
    for(index = 0; index < manager->allocated_elements; index++)
    {
        if(manager->name[index] == NULL)
        {
            break;
        }
    }

    // condition is true, means that there is need to allocate new space
    if(index == manager->allocated_elements)
    {
        manager->allocated_elements++;

        manager->name = (char**)realloc(manager->name, manager->allocated_elements * sizeof(char*));
        manager->mesh = (TE_Mesh*)realloc(manager->mesh, manager->allocated_elements * sizeof(TE_Mesh));

        index = manager->allocated_elements - 1; // get new index
    }

    manager->name[index] = (char*)malloc(strlen(path)+1); // allocate memory for name
    strcpy(manager->name[index], path);
    manager->mesh[index] = mesh; 

    return index;
}

inline void TE_sharedMesh_clear(TE_SharedMeshManager* manager, TE_SharedMesh mesh)
{
    TE_mesh_clear(&manager->mesh[mesh]);
    free(manager->name[mesh]);
    manager->name[mesh] = NULL;
}

inline void TE_sharedMesh_draw(TE_SharedMeshManager* manager, TE_SharedMesh mesh)
{
    TE_mesh_draw(&manager->mesh[mesh]);
}

inline void TE_sharedMesh_draw_instanced(TE_SharedMeshManager* manager, TE_SharedMesh mesh, unsigned int count)
{
    TE_mesh_draw_instanced(&manager->mesh[mesh], count);
}
