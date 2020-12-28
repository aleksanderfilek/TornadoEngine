#include"TE_physics2d.h"

#include<math.h>

int TE_collision_box2(float2* positionA, TE_Box2Collider* boxA, float2* positionB, TE_Box2Collider* boxB)
{
    float diff = positionA->x + boxA->size.x - positionB->x;
    if(diff < 0)    return -1;

    diff = positionB->x + boxB->size.x - positionA->x;
    if(diff < 0)    return -1;

    diff = positionA->y + boxA->size.y - positionB->y;
    if(diff < 0)    return -1;

    diff = positionB->y + boxB->size.y - positionA->y;

    return (diff < 0)?-1:0;
}

int TE_collision_circke_box(float2* positionA, TE_CircleCollider* circleA, float2* positionB, TE_Box2Collider* boxB)
{
    float dX = fabs(positionA->x - positionB->x);
    float dY = fabs(positionA->y - positionB->y);

    float diff = boxB->size.x*0.5f + circleA->radius - dX;
    if(diff < 0)    return -1;
    
    diff = boxB->size.y*0.5f + circleA->radius - dY;
    if(diff < 0)    return -1;

    diff = boxB->size.x*0.5f - dX;
    if(diff >= 0) return 0;

    diff = boxB->size.y*0.5f - dY;
    if(diff >= 0) return 0;

    diff = powf((dX - boxB->size.x*0.5f),2) + powf((dY - boxB->size.y*0.5f),2);
    diff -= powf(circleA->radius,2);

    return (diff <= 0)? 0 : -1; // need check
}

int TE_collision_circle2(float2* positionA, TE_CircleCollider* circleA, float2* positionB, TE_CircleCollider* circleB)
{
    float dX = positionA->x - positionB->x;
    float dY = positionA->y - positionB->y;
    float diff = dX*dX + dY*dY - (circleA->radius+circleB->radius)*(circleA->radius+circleB->radius);
    return diff;
}