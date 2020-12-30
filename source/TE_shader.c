#include"TE_shader.h"

#include<stdio.h>
#include<string.h>


TE_ShaderManager* TE_shaderManager_init(int size)
{
    TE_ShaderManager* manager = (TE_ShaderManager*)malloc(sizeof(TE_ShaderManager));
    
    manager->allocated_elements = size;

    manager->name = (char**)calloc(size, sizeof(char*));
    manager->gl_id = (unsigned int*)malloc(size * sizeof(unsigned int));
   
    return manager;
}

void TE_shaderManager_close(TE_ShaderManager* manager)
{

    for(int i = 0; i < manager->allocated_elements; i++)
    {
        if(manager->name[i] != NULL){
            free(manager->name[i]);
            glDeleteProgram(manager->gl_id[i]);
        }
    }
    free(manager->name);
    free(manager->gl_id);
    manager->allocated_elements = 0;

    free(manager);
}

TE_Shader TE_shader_load(TE_ShaderManager* manager, const char* path)
{
    // Check if shader was loaded
    // If was loaded return it
    int i;
    for(i = 0; i < manager->allocated_elements; i++)
    {
        if(manager->name[i] != NULL && strcmp(path, manager->name[i]) == 0)
        {
            return i;
        }
    }

    // Load shader from file
    FILE* file = fopen(path, "r");

    if(file == NULL){
        printf("Imposible to open the file!\n");
        return -1;
    }

    unsigned int vertex_shader_size = 1024;
    unsigned int vertex_shader_used_bytes = 0;
    char* vertex_shader_code = (char*)calloc(vertex_shader_size, sizeof(char));

    size_t fragment_shader_size = 1024;
    size_t fragment_shader_used_bytes = 0;
    char* fragment_shader_code = (char*)calloc(fragment_shader_size, sizeof(char));

    int shader_type = -1;

    char chunk[128];

    while(fgets(chunk, sizeof(chunk), file) != NULL)
    {
        if(strstr(chunk, "// vertex") != NULL)
        {
            shader_type = 0;
            //continue;
        }
        else if(strstr(chunk, "// fragment") != NULL)
        {
            shader_type = 1;
            //continue;
        }

        switch (shader_type)
        {
        case 0:
                if((vertex_shader_size - vertex_shader_used_bytes) < strlen(chunk)){
                    vertex_shader_code = (char*)realloc(vertex_shader_code, vertex_shader_size + 1024);
                    vertex_shader_size += 1024;
                }
                strcat(vertex_shader_code, chunk);
                vertex_shader_used_bytes += strlen(chunk);
            break;  
        case 1:
                if((fragment_shader_size - fragment_shader_used_bytes) < strlen(chunk)){
                    fragment_shader_code = (char*)realloc(fragment_shader_code, fragment_shader_size + 1024);
                    fragment_shader_size += 1024;
                }
                strcat(fragment_shader_code, chunk);
                fragment_shader_used_bytes += strlen(chunk);
            break;
        }
    }

    fclose(file);

    // Create shader program
    char vertex, fragment;

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, (const char**)&vertex_shader_code, NULL);
    glCompileShader(vertex);

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, (const char**)&fragment_shader_code, NULL);
    glCompileShader(fragment);

    unsigned int program = glCreateProgram();
    glAttachShader(program,vertex);
    glAttachShader(program,fragment);
    glLinkProgram(program);

    glDeleteShader(vertex);
    glDeleteShader(fragment);

    free(vertex_shader_code);
    free(fragment_shader_code);

    // Create shader
    int index;
    for(index = 0; index < manager->allocated_elements; index++)
    {
        if(manager->name[index] == NULL)
        {
            break;
        }
    }

    if(index == manager->allocated_elements)
    {
        manager->allocated_elements++;

        manager->name = (char**)realloc(manager->name, manager->allocated_elements * sizeof(char*));
        manager->gl_id = (unsigned int*)realloc(manager->gl_id, manager->allocated_elements * sizeof(unsigned int));

        index = manager->allocated_elements - 1; // get new index
    }

    manager->name[index] = (char*)malloc(strlen(path)+1);
    strcpy(manager->name[index], path);
    manager->gl_id[index] = program;
    
    return index;
}

void TE_shader_free(TE_ShaderManager* manager, TE_Shader shader)
{
    if(manager->name[shader] == NULL)
        return;

    free(manager->name[shader]);
    manager->name[shader] = NULL;
    glDeleteProgram(manager->gl_id[shader]);
}

inline void TE_shader_bind(TE_ShaderManager* manager, TE_Shader shader)
{
    glUseProgram(manager->gl_id[shader]);
}

inline unsigned int TE_shader_get_uniform_location(TE_ShaderManager* manager, TE_Shader shader, const char* name)
{
    glGetUniformLocation(manager->gl_id[shader], name);
}

