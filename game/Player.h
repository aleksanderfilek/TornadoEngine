#ifndef PLAYER_H_
#define PLAYER_H_

#include"TE.h"
#include"TE_math.h"

class Player{
private:
    float speed = 5.0f;

    float rotationSpeed = 45.0f;

    vector3f position = {0.0f,0.0f,0.0f};
    vector2f rotation;
public:
    Player();
    ~Player();

    void Update(float elapsedTime, vector3f& eyeposition, vector3f& forward);
    void Draw();
};

#endif