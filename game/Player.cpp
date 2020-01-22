#include"Player.h"

#include<cmath>
#include<iostream>

Player::Player(){
    
}

Player::~Player(){

}

void Player::Update(float elapsedTime, vector3f& eyeposition, vector3f& forward){
    const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );

    vector3f deltaPosition = {0.0f, 0.0f, 0.0f};
    if( currentKeyStates[ SDL_SCANCODE_LEFT ] )
    {
        deltaPosition+={speed * elapsedTime,0.0f,0.0f};
    }
    else if( currentKeyStates[ SDL_SCANCODE_RIGHT ] )
    {
        deltaPosition-={speed * elapsedTime,0.0f,0.0f};
    }

    if( currentKeyStates[ SDL_SCANCODE_UP ] )
    {
        deltaPosition+={0.0f,0.0f,speed * elapsedTime};
    }
    else if( currentKeyStates[ SDL_SCANCODE_DOWN] )
    {
        deltaPosition-={0.0f,0.0f,speed * elapsedTime};
    }

    float angle = DegreeToRadians(rotation.x);

    float x = deltaPosition.x*cosf(angle) - deltaPosition.z*sinf(angle);
    float y = deltaPosition.x*sinf(angle) + deltaPosition.z*cosf(angle);

    position += {x,0.0f,y};
    eyeposition = position;

    //std::cout<<position.x<<" / "<<position.y<<" / "<<position.z<<std::endl;

    if(currentKeyStates[SDL_SCANCODE_A]){
        rotation.x -= rotationSpeed*elapsedTime;
    }
    else if(currentKeyStates[SDL_SCANCODE_D]){
        rotation.x += rotationSpeed*elapsedTime;
    }

    vector3f rot = {0.0f, 0.0f, 1.0f};
    rot.x = -1.0f*sinf(angle);
    rot.z = cosf(angle);
    rot.normalize();

    forward = rot;
}

void Player::Draw(){

}