#ifndef TEMATH_H_
#define TEMATH_H_
#include<cmath>

struct Vector2f{
    float x,y;

    static Vector2f zero(){return {0.0f,0.0f};}
    static Vector2f one(){return {1.0f,1.0f};}
    static Vector2f up(){return {0.0f,1.0f};}
    static Vector2f right(){return {1.0f,0.0f};}

    float magnitude(){
        return sqrtf((x*x + y*y));
    }

    void normalize(){
        float length = magnitude();
        x /= length;
        y /= length;
    }

    static Vector2f normalized(const Vector2f *vector){
        float length = sqrtf(vector->x*vector->x + vector->y*vector->y);
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

    static Vector2i zero(){return {0,0};}
    static Vector2i one(){return {1,1};}
    static Vector2i up(){return {0,1};}
    static Vector2i right(){return {1,0};}

    float magnitude(){
        return sqrtf((float)(x*x + y*y));
    }

    void normalize(){
        double length = magnitude();
        x /= length;
        y /= length;
    }

    static Vector2i normalized(const Vector2i *vector){
        float length = sqrtf(vector->x*vector->x + vector->y*vector->y);
        Vector2i normilizedVector = {vector->x/length,vector->y/length};
        return normilizedVector;
    }

    Vector2i& operator+(const Vector2i &rhs){
        this->x + rhs.x;
        this->y + rhs.y;
        return *this;
    }

    Vector2i& operator-(const Vector2i &rhs){
        this->x - rhs.x;
        this->y - rhs.y;
        return *this;
    }
};
#endif