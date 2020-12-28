#ifndef TEPHYSICS2D_H_
#define TEPHYSICS2D_H_

#include"TE_math.h"

typedef struct 
{
    float radius;
}TE_CircleCollider;

typedef struct
{
    float2 size;
}TE_Box2Collider;

int TE_collision_box2(float2* positionA, TE_Box2Collider* boxA, float2* positionB, TE_Box2Collider* boxB);
int TE_collision_circke_box(float2* positionA, TE_CircleCollider* circleA, float2* positionB, TE_Box2Collider* boxB);
int TE_collision_circle2(float2* positionA, TE_CircleCollider* circleA, float2* positionB, TE_CircleCollider* circleB);


#endif