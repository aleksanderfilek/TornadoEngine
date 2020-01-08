#ifndef TEPHYSICS_H_
#define TEPHYSICS_H_

#include"TE_math.h"

struct BoxCollider{
    vector4 rect;
};

bool CheckCollision(const BoxCollider &A, const BoxCollider &B);

#endif