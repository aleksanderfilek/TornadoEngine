#include"TE_math.h"

#include<math.h>

float Vec2i_length(const Vector2i *vec){
    float length = vec->x*vec->x + vec->y*vec->y;
    return sqrtf(length);
}

void Vec2f_normalize(Vector2f *vec){
    float length = Vec2f_length(vec);
    vec->x /= length;
    vec->y /= length;
}

Vector2f Vec2f_normalized(const Vector2f *vec){
    float length = Vec2f_length(vec);
    float x = vec->x/length;
    float y = vec->y/length;
    Vector2f vector = {x,y};
    return vector;
}

float Vec2f_length(const Vector2f *vec){
    float length = vec->x*vec->x + vec->y*vec->y;
    return sqrtf(length);
}