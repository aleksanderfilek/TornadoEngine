#ifndef TEMATH_H_
#define TEMATH_H_

#define PI 3.141596f

#define Min(a, b) (a > b)?b:a
#define Max(a, b) (a > b)?a:b

typedef struct float2
{
    float x,y;
}float2;

float2 TE_add_f2(const float2* a, const float2* b);
float2 TE_substract_f2(const float2* a, const float2* b);
float2 TE_multiply_f2(const float2* a, float k);
float TE_dot_product_f2(const float2* a, const float2* b);
float TE_length_f2(const float2* vector);
float2 TE_normalized_f2(const float2* vector);
void TE_normalize_f2(float2* vector);

typedef struct float3
{
    float x,y,z;
}float3;

float3 TE_add_f3(const float3* a, const float3* b);
float3 TE_substract_f3(const float3* a, const float3* b);
float3 TE_multiply_f3(const float3* a, float k);
float TE_dot_product_f3(const float3* a, const float3* b);
float3 TE_cross_product_f3(const float3* a, const float3* b);
float TE_length_f3(const float3* vector);
float3 TE_normalized_f3(const float3* vector);
void TE_normalize_f3(float3* vector);

typedef float3 matrix3x3[3];

typedef struct float4
{
    float x,y,z,w;
}float4;

typedef struct
{
    float4 v[4];
}matrix4x4;

float TE_deg2rad(float degree);
float TE_rad2deg(float radians);

void TE_matrix_identity(matrix4x4* matrix);
void TE_matrix_projection(matrix4x4* matrix, int width, int height, float FOV, float near, float far);
void TE_matrix_orthographic(matrix4x4* matrix, int width, int height, float near, float far);
void TE_matrix_lookAt(matrix4x4* matrix, float3 eye, float3 target, float3 up);

void TE_matrix_translate(matrix4x4* matrix, float3 translation);
void TE_matrix_scale(matrix4x4* matrix, float3 scale);
void TE_matrix_rotateAxisX(matrix4x4* matrix, float angle);
void TE_matrix_rotateAxisY(matrix4x4* matrix, float angle);
void TE_matrix_rotateAxisZ(matrix4x4* matrix, float angle);
void TE_matrix_rotate(matrix4x4* matrix, float3 rotation);

typedef float4 quaternion;
quaternion TE_multiply_quaternion(const quaternion* A, const quaternion* B);
float3 TE_multiply_quaternion_f3(const quaternion* A, const float3* B);

#endif