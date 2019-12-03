#ifndef TEMATH_H_
#define TEMATH_H_

typedef struct 
{
    int x,y;
}Vector2i;

float Vec2i_length(const Vector2i *vec);

typedef struct 
{
    float x,y;
}Vector2f;

void Vec2f_normalize(Vector2f *vec);
Vector2f Vec2f_normalized(const Vector2f *vec);
float Vec2f_length(const Vector2f *vec);

#endif