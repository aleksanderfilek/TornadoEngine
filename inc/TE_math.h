#ifndef TEMATH_H_
#define TEMATH_H_

#include<cmath>

#define PI 3.141596f

struct vector2f
{
    float x,y;

    float length();
    void normalize();

    vector2f operator+(const vector2f& rhs);
    vector2f operator-(const vector2f& rhs);
    vector2f& operator=(const vector2f& rhs);
    vector2f& operator+=(const vector2f& rhs);
    vector2f& operator-=(const vector2f& rhs);
};

static vector2f normalized(vector2f &vector);
static vector2f crossProduct(vector2f &vectorA, vector2f &vectorB);

typedef vector2f mat2x2[2];

struct vector2i{
    int x,y;

    float length();

    vector2i operator+(const vector2i& rhs);
    vector2i operator-(const vector2i& rhs);
    vector2i& operator=(const vector2i& rhs);
    vector2i& operator+=(const vector2i& rhs);
    vector2i& operator-=(const vector2i& rhs);
};

struct vector2ui{
    unsigned int x,y;

    float length();

    vector2ui operator+(const vector2ui& rhs);
    vector2ui operator-(const vector2ui& rhs);
    vector2ui& operator=(const vector2ui& rhs);
    vector2ui& operator+=(const vector2ui& rhs);
    vector2ui& operator-=(const vector2ui& rhs);
};

struct vector3f{
    float x,y,z;

    float length();
    void normalize();

    vector3f operator-(const vector3f& rhs);
    vector3f operator+(const vector3f& rhs);
    vector3f& operator=(const vector3f& rhs);
    vector3f& operator+=(const vector3f& rhs);
    vector3f& operator-=(const vector3f& rhs);
};

vector3f normalized(vector3f &vector);
vector3f crossProduct(const vector3f &vectorA, const vector3f &vectorB);
float dotProduct(const vector3f &vectorA, const vector3f &vectorB);

struct vector3i{
    int x,y,z;
    
    float length();

    vector3f operator-(const vector3f& rhs);
    vector3f operator+(const vector3f& rhs);
    vector3f& operator=(const vector3f& rhs);
    vector3f& operator+=(const vector3f& rhs);
    vector3f& operator-=(const vector3f& rhs);
};

struct vector3ui{
    unsigned int x,y,z;

    float length();

    vector3f operator-(const vector3f& rhs);
    vector3f operator+(const vector3f& rhs);
    vector3f& operator=(const vector3f& rhs);
    vector3f& operator+=(const vector3f& rhs);
    vector3f& operator-=(const vector3f& rhs);
};

typedef vector3f mat3x3[3];

struct vector4f
{
    float x,y,z,w;

    float length();
    void normalize();

    vector3f operator-(const vector3f& rhs);
    vector3f operator+(const vector3f& rhs);
    vector3f& operator=(const vector3f& rhs);
    vector3f& operator+=(const vector3f& rhs);
    vector3f& operator-=(const vector3f& rhs);
};

typedef vector4f mat4x4[4];

float degreeToRadians(float degree);
float radiansToDegree(float radians);

const float *matrix_ptr(mat2x2 matrix);
const float *matrix_ptr(mat3x3 matrix);
const float *matrix_ptr(mat4x4 matrix);

void matrix_identity(mat4x4 &matrix);

void matrix_projection(mat4x4 &matrix, int width, int height, float FOV, float near, float far);
void matrix_orthographic(mat4x4 &matrix, int width, int height, float near, float far);
void matrix_lookAt(mat4x4 &matrix, vector3f &eye, vector3f &target, vector3f &up);

void matrix_translate(mat4x4 &matrix, vector3f translation);
void matrix_scale(mat4x4 &matrix, vector3f scale);
void matrix_rotateAxisX(mat4x4 &matrix, float angle);
void matrix_rotateAxisY(mat4x4 &matrix, float angle);
void matrix_rotateAxisZ(mat4x4 &matrix, float angle);
void matrix_rotate(mat4x4 &matrix, vector3f rotation);
#endif