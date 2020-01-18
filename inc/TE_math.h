#ifndef TEMATH_H_
#define TEMATH_H_

struct vector2f
{
    float x,y;
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
};

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

void matrix_translate(mat4x4 &matrix, vector3f translation);
void matrix_scale(mat4x4 &matrix, vector3f scale);
void matrix_rotateAxisX(mat4x4 &matrix, float angle);
void matrix_rotateAxisY(mat4x4 &matrix, float angle);
void matrix_rotateAxisZ(mat4x4 &matrix, float angle);
void matrix_rotate(mat4x4 &matrix, vector3f rotation);
#endif