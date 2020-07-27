#include"TE_math.h"

#include<math.h>
#include<string.h>

float2 TE_add_f2(const float2* a, const float2* b)
{
    float2 vec = {a->x + b->x, a->y + b->y};
    return vec;
}

float2 TE_substract_f2(const float2* a, const float2* b)
{
    float2 vec = {a->x - b->x, a->y - b->y};
    return vec;
}

float2 TE_multiply_f2(const float2* a, float k)
{
    float2 vec = {a->x * k, a->y * k};
    return vec;
}

inline float TE_dot_product_f2(const float2* a, const float2* b)
{
    return (a->x * b->x) + (a->y * b->y);
}

float TE_length_f2(const float2* vector)
{
    float x2 = vector->x * vector->x; 
    float y2 = vector->y * vector->y;
    return (float)sqrt(x2 + y2);
}

float2 TE_normalized_f2(const float2* vector)
{
    float length = TE_length_f2(vector);
    if(length == 0)
        return *vector;

    float x = vector->x / length;
    float y = vector->y / length;
    float2 normalized = {x, y};
    return normalized;
}
void TE_normalize_f2(float2* vector)
{
    float length = TE_length_f2(vector);
    if(length == 0)
        return;

    vector->x /= length;
    vector->y /= length;
}

float3 TE_add_f3(const float3* a, const float3* b)
{
    float3 vec = {a->x + b->x, a->y + b->y, a->z + b->z};
    return vec;
}

float3 TE_substract_f3(const float3* a, const float3* b)
{
    float3 vec = {a->x - b->x, a->y - b->y, a->z - b->z};
    return vec;
}

float3 TE_multiply_f3(const float3* a, float k)
{
    float3 vec = {a->x * k, a->y * k, a->z * k};
    return vec;
}

inline float TE_dot_product_f3(const float3* a, const float3* b)
{
    return (a->x * b->x) + (a->y * b->y) + (a->z * b->z); 
}

float3 TE_cross_product_f3(const float3* a, const float3* b)
{
    float3 vec = {a->y*b->z - a->z*b->y,
                a->z*b->x - a->x*b->z,
                a->x*b->y - a->y*b->x};
    return vec; 
}

float TE_length_f3(const float3* vector)
{
    float x2 = vector->x * vector->x; 
    float y2 = vector->y * vector->y;
    float z2 = vector->z * vector->z;
    return (float)sqrt(x2 + y2 + z2);
}

float3 TE_normalized_f3(const float3* vector)
{
    float length = TE_length_f3(vector);
    if(length == 0)
        return *vector;

    float x = vector->x / length;
    float y = vector->y / length;
    float z = vector->z / length;
    float3 normalized = {x, y, z};
    return normalized;
}
void TE_normalize_f3(float3* vector)
{
    float length = TE_length_f3(vector);
    if(length == 0)
        return;
        
    vector->x /= length;
    vector->y /= length;
    vector->z /= length;
}

inline float TE_deg2rad(float degree)
{
    return (degree * PI)/180.0f;
}

inline float TE_rad2deg(float radians)
{
    return (180.0f * radians)/PI;
}

void TE_matrix_identity(matrix4x4* matrix)
{
    memset(matrix, 0, sizeof(matrix4x4));
    matrix->v[0].x = 1.0f;
    matrix->v[1].y = 1.0f;
    matrix->v[2].z = 1.0f;
    matrix->v[3].w = 1.0f;
}

void TE_matrix_projection(matrix4x4* matrix, int width, int height, float FOV, float near, float far)
{
    float aspectRatio = (float)width/(float)height;
    float tg = tanf(FOV*0.5f*PI/180.0f);
    
    memset(matrix, 0, sizeof(matrix4x4));
    matrix->v[0].x = 1.0f/(aspectRatio*tg);
    // matrix->v[0].y = 0.0f;
    // matrix->v[0].z = 0.0f;
    // matrix->v[0].w = 0.0f;
    // matrix->v[1].x = 0.0f;
    matrix->v[1].y = 1.0f/tg;
    // matrix->v[1].z = 0.0f;
    // matrix->v[1].w = 0.0f;
    // matrix->v[2].x = 0.0f;
    // matrix->v[2].y = 0.0f;
    matrix->v[2].z = -far/(near - far);
    matrix->v[2].w = 1.0f;
    // matrix->v[3].x = 0.0f;
    // matrix->v[3].y = 0.0f;
    matrix->v[3].z = (far*near)/(near - far);
    // matrix->v[3].w = 0.0f;
}

void TE_matrix_orthographic(matrix4x4* matrix, int width, int height, float near, float far)
{

}

void TE_matrix_lookAt(matrix4x4* matrix, float3 eye, float3 target, float3 up)
{
    float3 f = TE_substract_f3(&target, &eye);
    TE_normalize_f3(&f);

    float3 r = TE_cross_product_f3(&f, &up);
    TE_normalize_f3(&r);

    float3 u = TE_cross_product_f3(&r, &f);

    // matrix->v[0].x = r.x;
    // matrix->v[0].y = r.y;
    // matrix->v[0].z = r.z;
    // matrix->v[0].w = 0.0f;

    // matrix->v[1].x = u.x;
    // matrix->v[1].y = u.y;
    // matrix->v[1].z = u.z;
    // matrix->v[1].w = 0.0f;

    // matrix->v[2].x = f.x;
    // matrix->v[2].y = f.y;
    // matrix->v[2].z = f.z;
    // matrix->v[2].w = 0.0f;

    matrix->v[0].x = r.x;
    matrix->v[1].x = r.y;
    matrix->v[2].x = r.z;

    matrix->v[0].y = u.x;
    matrix->v[1].y = u.y;
    matrix->v[2].y = u.z;

    matrix->v[0].z = f.x;
    matrix->v[1].z = f.y;
    matrix->v[2].z = f.z;

    matrix->v[0].w = 0.0f;
    matrix->v[1].w = 0.0f;
    matrix->v[2].w = 0.0f;

    // matrix->v[3].x = -eye.x;
    // matrix->v[3].y = -eye.y;
    // matrix->v[3].z = -eye.z;
    // matrix->v[3].w = 1.0f;

    matrix->v[3].x = -TE_dot_product_f3(&r,&eye);
    matrix->v[3].y = -TE_dot_product_f3(&u,&eye);
    matrix->v[3].z = -TE_dot_product_f3(&f,&eye);
    matrix->v[3].w = 1.0f;
}


void TE_matrix_translate(matrix4x4* matrix, float3 translation){
    matrix->v[3].x += translation.x;
    matrix->v[3].y += translation.y;
    matrix->v[3].z += translation.z;
}

void TE_matrix_scale(matrix4x4* matrix, float3 scale){
    matrix->v[0].x *= scale.x;
    matrix->v[1].y *= scale.y;
    matrix->v[2].z *= scale.z;
}

void TE_matrix_rotateAxisX(matrix4x4* matrix, float angle){
    float a = matrix->v[0].y;
    float b = matrix->v[0].z;
    matrix->v[0].y = a*cosf(angle) - b*sinf(angle);
    matrix->v[0].z = a*sinf(angle) + b*cosf(angle);
    a = matrix->v[1].y;
    b = matrix->v[1].z;
    matrix->v[1].y = a*cosf(angle) - b*sinf(angle);
    matrix->v[1].z = a*sinf(angle) + b*cosf(angle);
    a = matrix->v[2].y;
    b = matrix->v[2].z;
    matrix->v[2].y = a*cosf(angle) - b*sinf(angle);
    matrix->v[2].z = a*sinf(angle) + b*cosf(angle);
    a = matrix->v[3].y;
    b = matrix->v[3].z;   
    matrix->v[3].y = a*cosf(angle) - b*sinf(angle);
    matrix->v[3].z = a*sinf(angle) + b*cosf(angle);
}

void TE_matrix_rotateAxisY(matrix4x4* matrix, float angle){
    float a = matrix->v[0].x;
    float b = matrix->v[0].z;
    matrix->v[0].x = a*cosf(angle) + b*sinf(angle);
    matrix->v[0].z = -a*sinf(angle) + b*cosf(angle);
    a = matrix->v[1].x;
    b = matrix->v[1].z;
    matrix->v[1].x = a*cosf(angle) + b*sinf(angle);
    matrix->v[1].z = -a*sinf(angle) + b*cosf(angle);
    a = matrix->v[2].x;
    b = matrix->v[2].z;
    matrix->v[2].x = a*cosf(angle) + b*sinf(angle);
    matrix->v[2].z = -a*sinf(angle) + b*cosf(angle);
    a = matrix->v[3].x;
    b = matrix->v[3].z;   
    matrix->v[3].x = a*cosf(angle) + b*sinf(angle);
    matrix->v[3].z = -a*sinf(angle) + b*cosf(angle);
}

void TE_matrix_rotateAxisZ(matrix4x4* matrix, float angle){
    float a = matrix->v[0].x;
    float b = matrix->v[0].y;
    matrix->v[0].x = a*cosf(angle) + b*sinf(angle);
    matrix->v[0].y = -a*sinf(angle) + b*cosf(angle);
    a = matrix->v[1].x;
    b = matrix->v[1].y;
    matrix->v[1].x = a*cosf(angle) + b*sinf(angle);
    matrix->v[1].y = -a*sinf(angle) + b*cosf(angle);
    a = matrix->v[2].x;
    b = matrix->v[2].y;
    matrix->v[2].x = a*cosf(angle) + b*sinf(angle);
    matrix->v[2].y = -a*sinf(angle) + b*cosf(angle);
    a = matrix->v[3].x;
    b = matrix->v[3].y;   
    matrix->v[3].x = a*cosf(angle) + b*sinf(angle);
    matrix->v[3].y = -a*sinf(angle) + b*cosf(angle);
}

void TE_matrix_rotate(matrix4x4* matrix, float3 rotation){
    if(rotation.x != 0.0f)
        TE_matrix_rotateAxisX(matrix, rotation.x);
    if(rotation.y != 0.0f)
        TE_matrix_rotateAxisY(matrix, rotation.y);
    if(rotation.z != 0.0f)
        TE_matrix_rotateAxisZ(matrix, rotation.z);
}
