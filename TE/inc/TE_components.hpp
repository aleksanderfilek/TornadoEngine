#ifndef TECOMPONENTS_HPP_
#define TECOMPOENNTS_HPP_

#include"TE_math.hpp"

struct Transform2D{
    vector2f position;
    vector2f rotation;
    vector2f scale;
};

struct Transform{
    vector3f position;
    vector3f rotation;
    vector3f scale;
};

#endif