#include"TE_math.h"

#include<stdlib.h>

float *matrix_ptr(mat2x2 matrix){
    float *mat = (float *)malloc(4 * sizeof(float));
    mat[0] = matrix[0].x;
    mat[1] = matrix[0].y;
    mat[2] = matrix[1].x;
    mat[3] = matrix[1].y;
    return mat;
}

float *matrix_ptr(mat3x3 matrix){
    float *mat = (float *)malloc(9 * sizeof(float));
    mat[0] = matrix[0].x;
    mat[1] = matrix[0].y;
    mat[2] = matrix[0].z;
    mat[3] = matrix[1].x;
    mat[4] = matrix[1].y;
    mat[5] = matrix[1].z;    
    mat[6] = matrix[2].x;
    mat[7] = matrix[2].y;
    mat[8] = matrix[2].z;
    return mat;
}
float *matrix_ptr(mat4x4 matrix){
    float *mat = (float *)malloc(16 * sizeof(float));
    mat[0] = matrix[0].x;
    mat[1] = matrix[0].y;
    mat[2] = matrix[0].z;
    mat[3] = matrix[0].w;
    mat[4] = matrix[1].x;
    mat[5] = matrix[1].y;
    mat[6] = matrix[1].z;  
    mat[7] = matrix[1].w;  
    mat[8] = matrix[2].x;
    mat[9] = matrix[2].y;
    mat[10] = matrix[2].z;
    mat[11] = matrix[2].w;
    mat[12] = matrix[3].x;
    mat[13] = matrix[3].y;
    mat[14] = matrix[3].z;
    mat[15] = matrix[3].w;
    return mat;
}




