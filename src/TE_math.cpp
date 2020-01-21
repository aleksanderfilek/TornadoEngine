#include"TE_math.h"

#include<stdlib.h>

float vector2f::length(){
    float l = x*x + y*y;
    return sqrtf(l);
}

void vector2f::normalize(){
    float l = length();
    x/=l;
    y/=l;
}


// float *matrix_ptr(mat2x2 matrix){
//     float *mat = (float *)malloc(4 * sizeof(float));
//     mat[0] = matrix[0].x;
//     mat[1] = matrix[0].y;
//     mat[2] = matrix[1].x;
//     mat[3] = matrix[1].y;
//     return mat;
// }

// float *matrix_ptr(mat3x3 matrix){
//     float *mat = (float *)malloc(9 * sizeof(float));
//     mat[0] = matrix[0].x;
//     mat[1] = matrix[0].y;
//     mat[2] = matrix[0].z;
//     mat[3] = matrix[1].x;
//     mat[4] = matrix[1].y;
//     mat[5] = matrix[1].z;    
//     mat[6] = matrix[2].x;
//     mat[7] = matrix[2].y;
//     mat[8] = matrix[2].z;
//     return mat;
// }
// const float *matrix_ptr(mat4x4 matrix){
//     const float *mat[] = {
//         matrix[0].x,matrix[0].y,matrix[0].z, matrix[0].w,
//         matrix[1].x,matrix[1].y,matrix[1].z, matrix[1].w,
//         matrix[2].x,matrix[2].y,matrix[2].z, matrix[2].w,
//         matrix[3].x,matrix[3].y,matrix[3].z, matrix[3].w,
//     };

//     return mat;
// }

float DegreeToRadians(float degree){
    return (degree*PI)/180.0f;
}

vector3f crossProduct(const vector3f &vectorA, const vector3f &vectorB){
    vector3f vec;
    vec.x = vectorA.y*vectorB.z - vectorA.z*vectorB.y;
    vec.y = vectorA.z*vectorB.x - vectorA.x*vectorB.z;
    vec.z = vectorA.x*vectorB.y - vectorA.y*vectorB.x;
    return vec;
}

float dotProduct(const vector3f &vectorA, const vector3f &vectorB){
    float x = vectorA.x*vectorB.x;
    float y = vectorA.y*vectorB.y;
    float z = vectorA.z*vectorB.z;
    return x+y+z;
}

void matrix_projection(mat4x4 &matrix, int width, int height, float FOV, float near, float far){
    float aspectRatio = (float)height/(float)width;
    float tg = tanf(FOV*0.5f/180.0f*PI);
    matrix[0].x = aspectRatio*tg;
    matrix[0].y = 0.0f;
    matrix[0].z = 0.0f;
    matrix[0].w = 0.0f;
    matrix[1].x = 0.0f;
    matrix[1].y = tg;
    matrix[1].z = 0.0f;
    matrix[1].w = 0.0f;
    matrix[2].x = 0.0f;
    matrix[2].y = 0.0f;
    matrix[2].z = far/(far-near);
    matrix[2].w = 1.0f;
    matrix[3].x = 0.0f;
    matrix[3].y = 0.0f;
    matrix[3].z = -(far*near)/(far-near);
    matrix[3].w = 0.0f;
}

void matrix_orthographic(mat4x4 &matrix, int width, int height, float near, float far){
    matrix[0].x = 1.0f/(float)width;
    matrix[1].y = 1.0f/(float)height;
    matrix[2].z = -2.0f/(far-near);
    matrix[3].z = -(far+near)/(far-near);
    matrix[2].w = 1.0f;
}

void matrix_lookAt(mat4x4 &matrix, vector3f &eye, vector3f &target, vector3f &up){

    vector3f f = target - eye;
    f.normalize();
    vector3f u = up;
    u.normalize();
    vector3f s = crossProduct(f, u);
    u = crossProduct(s, f);

    matrix[0].x = s.x;
    matrix[1].x = s.y;
    matrix[2].x = s.z;
    matrix[3].x = 0.0f;
    matrix[0].y = u.x;
    matrix[1].y = u.y;
    matrix[2].y = u.z;
    matrix[3].y = 0.0f;
    matrix[0].z = -f.x;
    matrix[1].z = -f.y;
    matrix[2].z = -f.z;
    matrix[3].z = 0.0f;
    matrix[0].w = 0.0f;
    matrix[1].w = 0.0f;
    matrix[2].w = 0.0f;
    matrix[3].w = 1.0f;

    vector3f p = {-dotProduct(s,eye), -dotProduct(u,eye), -dotProduct(f,eye)};
    //vector3f p = {-eye.x, -eye.y, -eye.z};
    matrix_translate(matrix,p);
}

void matrix_identity(mat4x4 &matrix){
    matrix[0] = {1.0f, 0.0f, 0.0f, 0.0f};
    matrix[1] = {0.0f, 1.0f, 0.0f, 0.0f};
    matrix[2] = {0.0f, 0.0f, 1.0f, 0.0f};
    matrix[3] = {0.0f, 0.0f, 0.0f, 1.0f};
}

void matrix_translate(mat4x4 &matrix, vector3f translation){
    matrix[3].x += translation.x;
    matrix[3].y += translation.y;
    matrix[3].z += translation.z;
}

void matrix_scale(mat4x4 &matrix, vector3f scale){
    matrix[0].x *= scale.x;
    matrix[1].y *= scale.y;
    matrix[2].z *= scale.z;
}

void matrix_rotateAxisX(mat4x4 &matrix, float angle){
    float a = matrix[0].y, b = matrix[0].z;
    matrix[0].y = a*cosf(angle) - b*sinf(angle);
    matrix[0].z = a*sinf(angle) + b*cosf(angle);
    a = matrix[1].y;
    b = matrix[1].z;
    matrix[1].y = a*cosf(angle) - b*sinf(angle);
    matrix[1].z = a*sinf(angle) + b*cosf(angle);
    a = matrix[2].y;
    b = matrix[2].z;
    matrix[2].y = a*cosf(angle) - b*sinf(angle);
    matrix[2].z = a*sinf(angle) + b*cosf(angle);
    a = matrix[3].y;
    b = matrix[3].z;   
    matrix[3].y = a*cosf(angle) - b*sinf(angle);
    matrix[3].z = a*sinf(angle) + b*cosf(angle);
}

void matrix_rotateAxisY(mat4x4 &matrix, float angle){
    float a = matrix[0].x, b = matrix[0].z;
    matrix[0].x = a*cosf(angle) + b*sinf(angle);
    matrix[0].z = -a*sinf(angle) + b*cosf(angle);
    a = matrix[1].x;
    b = matrix[1].z;
    matrix[1].x = a*cosf(angle) + b*sinf(angle);
    matrix[1].z = -a*sinf(angle) + b*cosf(angle);
    a = matrix[2].x;
    b = matrix[2].z;
    matrix[2].x = a*cosf(angle) + b*sinf(angle);
    matrix[2].z = -a*sinf(angle) + b*cosf(angle);
    a = matrix[3].x;
    b = matrix[3].z;   
    matrix[3].x = a*cosf(angle) + b*sinf(angle);
    matrix[3].z = -a*sinf(angle) + b*cosf(angle);
}

void matrix_rotateAxisZ(mat4x4 &matrix, float angle){
    float a = matrix[0].x, b = matrix[0].y;
    matrix[0].x = a*cosf(angle) + b*sinf(angle);
    matrix[0].y = -a*sinf(angle) + b*cosf(angle);
    a = matrix[1].x;
    b = matrix[1].y;
    matrix[1].x = a*cosf(angle) + b*sinf(angle);
    matrix[1].y = -a*sinf(angle) + b*cosf(angle);
    a = matrix[2].x;
    b = matrix[2].y;
    matrix[2].x = a*cosf(angle) + b*sinf(angle);
    matrix[2].y = -a*sinf(angle) + b*cosf(angle);
    a = matrix[3].x;
    b = matrix[3].y;   
    matrix[3].x = a*cosf(angle) + b*sinf(angle);
    matrix[3].y = -a*sinf(angle) + b*cosf(angle);
}

void matrix_rotate(mat4x4 &matrix, vector3f rotation){
    if(rotation.x != 0.0f)
        matrix_rotateAxisX(matrix,rotation.x);
    if(rotation.y != 0.0f)
        matrix_rotateAxisY(matrix,rotation.y);
    if(rotation.z != 0.0f)
        matrix_rotateAxisZ(matrix,rotation.z);
}




