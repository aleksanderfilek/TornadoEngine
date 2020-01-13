#ifndef TEMATH_H_
#define TEMATH_H_

struct vector2
{
    float x,y;
};

typedef vector2 mat2x2[2];



struct vector3{
    float x,y,z;
};

typedef vector3 mat3x3[3];

struct vector4
{
    float x,y,z,w;
};

typedef vector4 mat4x4[4];

float *matrix_ptr(mat2x2 matrix);
float *matrix_ptr(mat3x3 matrix);
float *matrix_ptr(mat4x4 matrix);



#endif