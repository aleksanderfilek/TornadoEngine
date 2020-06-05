#include"TE_graphics.h"

#include<stdio.h>
#include<iostream>


extern TornadoEngine engine;
extern TextureManager textureManager;

int Clear(){ 
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    return 1;
}

int SetDrawColor(uint8_t R, uint8_t G, uint8_t B, uint8_t A){ 
        glClearColor((float)R/255.0f,
                 (float)G/255.0f,
                 (float)B/255.0f,
                 (float)A/255.0f);
        return 1;
}

void Render(){ 
    SDL_GL_SwapWindow(engine.GetWindow());
 }

unsigned int TextureManager::LoadTexture(std::string path){
    int width, height;
    unsigned char *image = SOIL_load_image(path.c_str(), &width, &height, 0, SOIL_LOAD_RGBA);

    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, 
        GL_RGBA, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);

    SOIL_free_image_data(image);
    glBindTexture(GL_TEXTURE_2D, 0);

    this->textures.push_back({texture, width, height });

    unsigned int id = this->textures.size() - 1;

    this->textures_organizer[path] = id;

    return id;
}

void TextureManager::Bind(unsigned int count, unsigned int *textureID){
    for(int i = 0; i < count; i++){
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, this->textures[*textureID].id);
    }
}

void TextureManager::DestroyTexture(unsigned int textureID){
    glDeleteTextures(1, &this->textures[textureID].id);

    for(auto it = std::begin(this->textures_organizer); it != std::end(this->textures_organizer); ++it){
        this->textures_organizer.erase(it);
    }

}

void TextureManager::GetTextureSize(unsigned int textureID, int *width, int *height){
    if(width != NULL)
        *width = this->textures[textureID].width;
    if(height != NULL)
        *height = this->textures[textureID].height;
}

bool TextureManager::GetTextureID(std::string textureName, unsigned int *id){
    bool success = this->textures_organizer.count(textureName);
    if(success == false)
        return false;

    if(id != NULL)
        *id = this->textures_organizer[textureName];

    return true;
}

TextureManager::~TextureManager(){
    for(int i = 0; i < this->textures.size(); i++){
        glDeleteTextures(1, &this->textures[i].id);
    }
    this->textures.clear();
    this->textures_organizer.clear();
}


Mesh::Mesh(std::vector<Vertex> _vertices, std::vector<unsigned int> _indices, bool saveData){
    this->vertices.swap(_vertices);
    this->indices.swap(_indices);
    
    this->textures = NULL;
    this->texturesCount = 0;

    this->setupMesh();

    if(saveData == false){
        this->vertices.clear();
        this->indices.clear();
    }
}

Mesh::~Mesh(){
    this->Clear(false);
}

void Mesh::setupMesh(){

        glGenVertexArrays(1, &this->VAO);
        glGenBuffers(1, &this->VBO);
        glGenBuffers(1, &this->EBO);

        glBindVertexArray(this->VAO);
        glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
        glBufferData(GL_ARRAY_BUFFER,this->vertices.size() * sizeof(Vertex), &this->vertices[0], GL_STATIC_DRAW);  

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(unsigned int), &this->indices[0], GL_STATIC_DRAW);


        glEnableVertexAttribArray(0);	
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(1);	
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3* sizeof(GLfloat)));
        glEnableVertexAttribArray(2);	
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));

        glBindVertexArray(0);
}

void Mesh::SetTextures(unsigned int count, unsigned int *_textures){
    if(this->textures != NULL){
        delete [] this->textures;
    }

    this->texturesCount = count;

    this->textures = new unsigned int[count];
    for(int i = 0; i < count; i++){
        this->textures[i] = _textures[i];
    }
}

void Mesh::Clear(bool onlyData){
    this->vertices.clear();
    this->indices.clear();
    if(this->textures != NULL){
        delete [] this->textures;
    }

    if(onlyData == false){
        glDeleteVertexArrays(1, &this->VAO);
        glDeleteBuffers(1, &this->VBO);
        glDeleteBuffers(1, &this->EBO);
    }
}

void Draw(const Mesh& mesh){

    if(mesh.texturesCount > 0){
        textureManager.Bind(mesh.texturesCount, mesh.textures);
    }

    glBindVertexArray(mesh.VAO);
    glDrawElements(GL_TRIANGLES, mesh.indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void DrawInstanced(int count, const Mesh& mesh){
        if(mesh.texturesCount > 0){
        textureManager.Bind(mesh.texturesCount, mesh.textures);
    }

    glBindVertexArray(mesh.VAO);
    glDrawElementsInstanced(GL_TRIANGLES, mesh.indices.size(), GL_UNSIGNED_INT, 0, count);
    glBindVertexArray(0);
}


bool Mesh::Load(std::string path){
    std::vector<float3> temp_vertices;
    std::vector<float3> temp_normalVertices;
    std::vector<float2> temp_uvs;
    std::vector<Vertex> _vertices;
    std::vector<unsigned int> _indices;

    FILE *file = fopen(path.c_str(),"r");
    if(file == NULL){
        std::cout<<"Imposible to open the file !"<<std::endl;
        return false;
    }

    while(1){
        char lineHeader[128];
        int res = fscanf(file, "%s", lineHeader);
        if (res == EOF)
            break; 

        if(strcmp( lineHeader, "vt" ) == 0){
            float2 uv;
            fscanf(file, "%f %f\n", &uv.x, &uv.y);
            temp_uvs.push_back(uv);
        }
        else if(strcmp( lineHeader, "vn" ) == 0){
            float3 normal;
            fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
            temp_normalVertices.push_back(normal);
        }
        else if(strcmp( lineHeader, "v" ) == 0){
            float3 vertex;
            fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
            temp_vertices.push_back(vertex);
        }
        else if(strcmp( lineHeader, "f" ) == 0){
            int f1, f2, f3, f4, f5, f6, f7, f8, f9;
            fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n",&f1,&f2,&f3,&f4,&f5,&f6,&f7,&f8,&f9);

            Vertex v0,v1,v2;

            v0.position = temp_vertices[f1-1];
            v0.textureCoord = temp_uvs[f2-1];
            v0.normal = temp_normalVertices[f3-1]; 

            v1.position = temp_vertices[f4-1];
            v1.textureCoord = temp_uvs[f5-1];
            v1.normal = temp_normalVertices[f6-1]; 

            v2.position = temp_vertices[f7-1];
            v2.textureCoord = temp_uvs[f8-1];
            v2.normal = temp_normalVertices[f9-1]; 

            _vertices.push_back(v0);
            _indices.push_back(_vertices.size()-1);
            _vertices.push_back(v1);
            _indices.push_back(_vertices.size()-1);
            _vertices.push_back(v2);
            _indices.push_back(_vertices.size()-1);

        }
    }

    fclose(file);

    temp_vertices.clear();
    temp_normalVertices.clear();
    temp_uvs.clear();

    this->vertices.swap(_vertices);
    this->indices.swap(_indices);

    _vertices.clear();
    _indices.clear();

    //this->Clear(false);
    this->setupMesh();

    return true;
}

void Shader::Load(std::string path){
    std::string vertexCode;
    std::string fragmentCode;

    std::ifstream shaderFile;
    shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    int shaderType = 0;

    try{
        shaderFile.open(path);

        while(!shaderFile.eof()){
            char line[256];
            shaderFile.getline(line, 256);

            if(strstr(line, "#vertex")){
                shaderType = 0;
            }
            else if(strstr(line, "#fragment")){
                shaderType = 1;
            }
            else{
                switch (shaderType)
                {
                case 0:
                    vertexCode.append(line);
                    vertexCode.append("\n");
                    break;
                case 1:
                    fragmentCode.append(line);
                    fragmentCode.append("\n");
                    break;
                }

                if(strstr(line, "uniform")){
                    char *uniform;
                    char *pch;
                    pch = strtok(line," ;");
                    while(pch != NULL){
                        uniform = pch;
                        pch = strtok(NULL," ;");
                    }

                    std::string sUniform;
                    sUniform.append(uniform);

                    this->uniform_Loc[sUniform] = 0;
                }
            }
        }
        shaderFile.close();
    }
    catch(std::ifstream::failure e){
        printf("ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ\n");
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

    this->ID = program;

    this->Bind();
    for (std::map<std::string,unsigned int>::iterator it=this->uniform_Loc.begin(); it!=this->uniform_Loc.end(); ++it){
        it->second = glGetUniformLocation(this->ID, it->first.c_str());
    }
}

void Shader::Bind(){
    glUseProgram(this->ID);
}