#ifndef TEDEBUG_H_
#define TEDEBUG_H_

#include"TE_math.hpp"

void Debug_setColor(float r, float g, float b);
void Debug_setColor(vector3f color);

void Debug_drawLine(vector3f startPosition, vector3f endPosition);

void Debug_drawSquare(vector2f center, vector2f size);
void Debug_drawCircle(vector2f center, float radius);

void Debug_drawCube(vector3f center, vector3f size);
void Debug_drawSphere(vector3f center, float radius);

#endif
