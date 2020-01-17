#include"TE_math.h"

#include<stdlib.h>
#include<cmath>

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

void matrix_rotate(mat4x4 &matrix, vector3f rotation){
    matrix[0].x += cosf(rotation.y)*cosf(rotation.z);
    matrix[0].y += (cosf(rotation.x)*sinf(rotation.z) + sinf(rotation.x)*sinf(rotation.y)*cosf(rotation.z));
    matrix[0].z += (sinf(rotation.x)*sinf(rotation.z) - cosf(rotation.x)*sinf(rotation.y)*cosf(rotation.z));
    matrix[1].x += -cosf(rotation.y)*sinf(rotation.z);
    matrix[1].y += (cosf(rotation.x)*cosf(rotation.z) - sinf(rotation.x)*sinf(rotation.y)*sinf(rotation.z));
    matrix[1].z += (sinf(rotation.x)*cosf(rotation.z) + cosf(rotation.x)*sinf(rotation.y)*sinf(rotation.z));
    matrix[2].x += sinf(rotation.y);
    matrix[2].y += -sinf(rotation.x)*cosf(rotation.y);
    matrix[2].z += cosf(rotation.x)*cosf(rotation.y);
}



