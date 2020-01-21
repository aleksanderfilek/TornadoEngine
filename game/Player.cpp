#include"Player.h"

#include<cmath>
#include<iostream>

Player::Player(){
    
}

Player::~Player(){

}

void Player::Update(float elapsedTime, vector3f& eyeposition, vector3f& forward){
    const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );

    if( currentKeyStates[ SDL_SCANCODE_LEFT ] )
    {
        position+={speed * elapsedTime,0.0f,0.0f};
    }
    else if( currentKeyStates[ SDL_SCANCODE_RIGHT ] )
    {
        position-={speed * elapsedTime,0.0f,0.0f};
    }

    if( currentKeyStates[ SDL_SCANCODE_UP ] )
    {
        position+={0.0f,0.0f,speed * elapsedTime};
    }
    else if( currentKeyStates[ SDL_SCANCODE_DOWN] )
    {
        position-={0.0f,0.0f,speed * elapsedTime};
    }
    eyeposition = position;

    if(currentKeyStates[SDL_SCANCODE_A]){
        rotation.x += rotationSpeed*elapsedTime;
    }
    else if(currentKeyStates[SDL_SCANCODE_D]){
        rotation.x -= rotationSpeed*elapsedTime;
    }

    float angle = DegreeToRadians(rotation.x);
    vector3f rot = {0.0f, 0.0f, 1.0f};
    rot.x = -1.0f*sinf(angle);
    rot.z = cosf(angle);
    rot.normalize();
    std::cout<<rot.x<<" "<<rot.y<<" "<<rot.z<<std::endl;

    forward = rot;
}

void Player::Draw(){

}