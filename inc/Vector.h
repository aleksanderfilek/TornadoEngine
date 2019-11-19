#ifndef VECTOR_H_
#define VECTOR_H_

#include<cmath>

struct Vector2f{
    float x,y;

    static Vector2f zero(){return {0.0f,0.0f};}
    static Vector2f one(){return {1.0f,1.0f};}
    static Vector2f up(){return {0.0f,1.0f};}
    static Vector2f right(){return {1.0f,0.0f};}

    static void normalize(Vector2f &vector){
        float length = sqrt(vector.x*vector.x + vector.y*vector.y);
        vector.x /= length;
        vector.y /= length;
    }

    static Vector2f normalized(const Vector2f *vector){
        float length = sqrt(vector->x*vector->x + vector->y*vector->y);
        Vector2f normilizedVector = {vector->x/length,vector->y/length};
        return normilizedVector;
    }

    Vector2f& operator+(const Vector2f &rhs){
        this->x + rhs.x;
        this->y + rhs.y;
        return *this;
    }

    Vector2f& operator-(const Vector2f &rhs){
        this->x - rhs.x;
        this->y - rhs.y;
        return *this;
    }
};

struct Vector2i{
    int x,y;
};


#endif