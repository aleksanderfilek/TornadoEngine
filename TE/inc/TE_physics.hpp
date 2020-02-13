#ifndef TEPHYSICS_HPP_
#define TEPHYSICS_HPP_

#include "TE_math.hpp"

struct BoxCollider2D{
    vector2f position;
    vector2f size;
};

void CreateBoxCollider2D(vector2f _position, vector2f _size, bool isStatic);
bool BoxCollision2D(const BoxCollider2D &colliderA, const BoxCollider2D &colliderB);

struct CircleCollider2D{
    vector2f position;
    float radius;
};

void CreateCircleCollider2D(vector2f _position, float _radius, bool isStatic);

#endif