#include"TE_debug.hpp"

vector3f color;


void Debug_setColor(float r, float g, float b){
    color = {r,g,b};
}

void Debug_setColor(vector3f Color){
    color = Color;
}
