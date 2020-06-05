#ifndef TEMATH_H_
#define TEMATH_H_
#include<cmath>

#define PI 3.141596f

struct float2
{
    float x,y;
};

static float2 operator+(const float2& v1, const float2& v2);
static float2 operator-(const float2& v1, const float2& v2);
static float2& operator+=(float2& v1, const float2& v2);
static float2& operator-=(float2& v1, const float2& v2);
static float2& operator*(float2& v, float factor);
static float2& operator*(float factor, float2& v);

static float length(const float2 &vector);
static float2 normalize(const float2 &vector);
static float dotProduct(const float2 &vectorA, const float2 &vectorB);

typedef float2 matrix2x2[2];

struct float3{
    float x,y,z;
};

static float3 operator-(const float3& v1, const float3& v2);
static float3 operator+(const float3& v1, const float3& v2);
static float3& operator+=(float3& v1, const float3& v2);
static float3& operator-=(float3& v1, const float3& v2);
static float3& operator*(float3& v, float factor);
static float3& operator*(float factor, float3& v);

static float length(const float3 &vector);
static float3 normalize(const float3 &vector);
static float3 crossProduct(const float3 &vectorA, const float3 &vectorB);
static float dotProduct(const float3 &vectorA, const float3 &vectorB);

typedef float3 matrix3x3[3];

struct float4
{
    float x,y,z,w;
};

typedef float4 matrix4x4[4];

static float deg2rad(float degree);
static float rad2deg(float radians);

static void matrix_identity(matrix4x4 &matrix);

static void matrix_projection(matrix4x4 &matrix, int width, int height, float FOV, float near, float far);
static void matrix_orthographic(matrix4x4 &matrix, int width, int height, float near, float far);
static void matrix_lookAt(matrix4x4 &matrix, float3 &eye, float3 &target, float3 &up);

static void matrix_translate(matrix4x4 &matrix, float3 translation);
static void matrix_scale(matrix4x4 &matrix, float3 scale);
static void matrix_rotateAxisX(matrix4x4 &matrix, float angle);
static void matrix_rotateAxisY(matrix4x4 &matrix, float angle);
static void matrix_rotateAxisZ(matrix4x4 &matrix, float angle);
static void matrix_rotate(matrix4x4 &matrix, float3 rotation);

#endif