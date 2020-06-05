#include"TE_math.h"

#include<cstring>
#include<stdlib.h>


float2 operator+(const float2& v1, const float2& v2){
    float2 vec;
    vec.x = v1.x + v2.x;
    vec.y = v1.y + v2.y;
    return vec;
}

float2 operator-(const float2& v1, const float2& v2){
    float2 vec;
    vec.x = v1.x - v2.x;
    vec.y = v1.y - v2.y;
    return vec;
}

float2& operator+=(float2& v1, const float2& v2){
        v1.x += v2.x;
        v1.y += v2.y;
        return v1;
}

float2& operator-=(float2& v1, const float2& v2){
    v1.x -= v2.x;
    v1.y -= v2.y;
    return v1;
}

float2& operator*(float2& v, float factor){
    v.x *= factor;
    v.y *= factor;
    return v;
}

float2& operator*(float factor, float2& v){
    v.x *= factor;
    v.y *= factor;
    return v;
}

float length(const float2 &vector){
    float len = vector.x*vector.x + vector.y*vector.y;
    len = sqrtf(len);
    return len;
}

float2 normalize(const float2 &vector){
    float2 vec;
    float l = length(vector);
    vec.x = vector.x/l;
    vec.y = vector.y/l;
    return vec;
}

float dotProduct(const float2& vectorA, const float2& vectorB){
    return vectorA.x*vectorB.x + vectorA.y*vectorB.y;
}

float3 operator+(const float3& v1, const float3& v2){
    float3 vec;
    vec.x = v1.x + v2.x;
    vec.y = v1.y + v2.y;
    vec.z = v1.z + v2.z;
    return vec;
}

float3 operator-(const float3& v1, const float3& v2){
    float3 vec;
    vec.x = v1.x - v2.x;
    vec.y = v1.y - v2.y;
    vec.z = v1.z - v2.z;
    return vec;
}

float3& operator+=(float3& v1, const float3& v2){
    v1.x += v2.x;
    v1.y += v2.y;
    v1.z += v2.z;
    return v1;
}

float3& operator-=(float3& v1, const float3& v2){
    v1.x -= v2.x;
    v1.y -= v2.y;
    v1.z -= v2.z;
    return v1;
}

float3& operator*(float3& v, float factor){
    v.x *= factor;
    v.y *= factor;
    v.z *= factor;
    return v;
}

float3& operator*(float factor, float3& v){
    v.x *= factor;
    v.y *= factor;
    v.z *= factor;
    return v;
}

float length(const float3 &vector){
    float len = vector.x*vector.x;
    len += vector.y*vector.y;
    len += vector.z*vector.z;
    len = sqrtf(len);
    return len;
}

float3 normalize(const float3 &vector){
    float3 vec;
    float l = length(vector);
    vec.x = vector.x/l;
    vec.y = vector.y/l;
    vec.z = vector.z/l;
    return vec;
}

float3 crossProduct(const float3 &vectorA, const float3 &vectorB){
    float3 vec;
    vec.x = vectorA.y*vectorB.z - vectorA.z*vectorB.y;
    vec.y = vectorA.z*vectorB.x - vectorA.x*vectorB.z;
    vec.z = vectorA.x*vectorB.y - vectorA.y*vectorB.x;
    return vec;
}

float dotProduct(const float3 &vectorA, const float3 &vectorB){
    float x = vectorA.x*vectorB.x;
    float y = vectorA.y*vectorB.y;
    float z = vectorA.z*vectorB.z;
    return x+y+z;
}

float deg2rad(float degree){
    return (degree * PI)/180.0f;
}

float rad2deg(float radians){
    return (180.0f * radians)/PI;
}

void matrix_projection(matrix4x4 &matrix, int width, int height, float FOV, float near, float far){
    float aspectRatio = (float)height/(float)width;
    float tg = tanf(FOV*0.5f/180.0f*PI);
    memset(&matrix, 0, sizeof(matrix4x4));
    matrix[0].x = aspectRatio*tg;
    // matrix[0].y = 0.0f;
    // matrix[0].z = 0.0f;
    // matrix[0].w = 0.0f;
    // matrix[1].x = 0.0f;
    matrix[1].y = tg;
    // matrix[1].z = 0.0f;
    // matrix[1].w = 0.0f;
    // matrix[2].x = 0.0f;
    // matrix[2].y = 0.0f;
    matrix[2].z = far/(far-near);
    matrix[2].w = 1.0f;
    // matrix[3].x = 0.0f;
    // matrix[3].y = 0.0f;
    matrix[3].z = -(far*near)/(far-near);
    // matrix[3].w = 0.0f;
}

void matrix_orthographic(matrix4x4 &matrix, int width, int height, float near, float far){
    matrix[0].x = 1.0f/(float)width;
    matrix[1].y = 1.0f/(float)height;
    matrix[2].z = -2.0f/(far-near);
    matrix[3].z = -(far+near)/(far-near);
    matrix[2].w = 1.0f;
}

void matrix_lookAt(matrix4x4 &matrix, float3 &eye, float3 &target, float3 &up){

    float3 f = target - eye;
    f = normalize(f);
    float3 u = up;
    u = normalize(u);
    float3 s = crossProduct(f, u);
    u = crossProduct(s, f);

    matrix[0].x = s.x;
    matrix[0].y = s.y;
    matrix[0].z = s.z;
    matrix[3].x = -dotProduct(s,eye);
    matrix[1].x = u.x;
    matrix[1].y = u.y;
    matrix[1].z = u.z;
    matrix[3].y =  -dotProduct(u,eye);
    matrix[2].x = -f.x;
    matrix[2].y = -f.y;
    matrix[2].z = -f.z;
    matrix[3].z = -dotProduct(f,eye);
    matrix[0].w = 0.0f;
    matrix[1].w = 0.0f;
    matrix[2].w = 0.0f;
    matrix[3].w = 1.0f;
}

void matrix_identity(matrix4x4 &matrix){
    matrix[0] = {1.0f, 0.0f, 0.0f, 0.0f};
    matrix[1] = {0.0f, 1.0f, 0.0f, 0.0f};
    matrix[2] = {0.0f, 0.0f, 1.0f, 0.0f};
    matrix[3] = {0.0f, 0.0f, 0.0f, 1.0f};
}

void matrix_translate(matrix4x4 &matrix, float3 translation){
    matrix[3].x += translation.x;
    matrix[3].y += translation.y;
    matrix[3].z += translation.z;
}

void matrix_scale(matrix4x4 &matrix, float3 scale){
    matrix[0].x *= scale.x;
    matrix[1].y *= scale.y;
    matrix[2].z *= scale.z;
}

void matrix_rotateAxisX(matrix4x4 &matrix, float angle){
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

void matrix_rotateAxisY(matrix4x4 &matrix, float angle){
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

void matrix_rotateAxisZ(matrix4x4 &matrix, float angle){
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

void matrix_rotate(matrix4x4 &matrix, float3 rotation){
    if(rotation.x != 0.0f)
        matrix_rotateAxisX(matrix,rotation.x);
    if(rotation.y != 0.0f)
        matrix_rotateAxisY(matrix,rotation.y);
    if(rotation.z != 0.0f)
        matrix_rotateAxisZ(matrix,rotation.z);
}
