#ifndef TEMATH_H_
#define TEMATH_H_

#include<cmath>

#define PI 3.141596f

struct vector2f
{
    float x,y;

    float length();
    void normalize();

    static vector2f normalized(vector2f &vector){
        vector2f vec;
        float l = vector.length();
        vec.x = vector.x/l;
        vec.y = vector.y/l;
        return vec;
    }

    vector2f& operator+=(const vector2f& rhs){
        x += rhs.x;
        y += rhs.y;
        return *this;
    }

    vector2f& operator-=(const vector2f& rhs){
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }
};

typedef vector2f mat2x2[2];

struct vector2i{
    int x,y;
};

struct vector2ui{
    unsigned int x,y;
};

struct vector3f{
    float x,y,z;

    float length(){
        float l = x*x + y*y +z*z;
        return sqrtf(l);
    }

    void normalize(){
        float l = length();
        x/=l;
        y/=l;
        z/=l;
    }

    static vector3f normalized(vector3f &vector){
        vector3f vec;
        float l = vector.length();
        vec.x = vector.x/l;
        vec.y = vector.y/l;
        vec.z = vector.z/l;
        return vec;
    }
    vector3f operator-(const vector3f& rhs){
        vector3f vec;
        vec.x = x - rhs.x;
        vec.y = y - rhs.y;
        vec.z = z - rhs.z;
        return vec;
    }
    vector3f operator+(const vector3f& rhs){
        vector3f vec;
        vec.x = x + rhs.x;
        vec.y = y + rhs.y;
        vec.z = z + rhs.z;
        return vec;
    }
    vector3f& operator+=(const vector3f& rhs){
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
        return *this;
    }

    vector3f& operator-=(const vector3f& rhs){
        x -= rhs.x;
        y -= rhs.y;
        z -= rhs.z;
        return *this;
    }

};

float DegreeToRadians(float degree);

vector3f crossProduct(const vector3f &vectorA, const vector3f &vectorB);
float dotProduct(const vector3f &vectorA, const vector3f &vectorB);

struct vector3i{
    int x,y,z;
};

struct vector3ui{
    unsigned int x,y,z;
};

typedef vector3f mat3x3[3];

struct vector4f
{
    float x,y,z,w;
};

typedef vector4f mat4x4[4];

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