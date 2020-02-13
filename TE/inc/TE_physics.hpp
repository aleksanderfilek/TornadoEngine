#ifndef TEPHYSICS_HPP_
#define TEPHYSICS_HPP_

#include "TE_math.hpp"

struct BoxCollider2D{
    vector2f position;
    vector2f size;
};

bool BoxCollision2D(const BoxCollider2D &colliderA, const BoxCollider2D &colliderB);

struct CircleCollider2D{
    vector2f position;
    float radius;
};

bool CircleCollision2D(const CircleCollider2D &colliderA, const CircleCollider2D &colliderB);

bool Box_CircleCollision2D(const BoxCollider2D &colliderA, const CircleCollider2D &colliderB);

struct Rigidbody2D{
    vector2f velocity;
};

struct BoxCollider{
    vector3f position;
    vector3f size;
};

struct SphereCollider
{
    vector3f position;
    float radius;
};

struct Rigidbody{
    vector3f velocity;
};

#endif