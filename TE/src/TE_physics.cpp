#include"TE_physics.hpp"

bool BoxCollision2D(const BoxCollider2D &colliderA, const BoxCollider2D &colliderB){
    float d1x = colliderB.position.x - colliderA.position.x - colliderA.size.x;
    float d1y = colliderB.position.y - colliderA.position.y - colliderA.size.y;
    float d2x = colliderA.position.x - colliderB.position.x - colliderB.size.x;
    float d2y = colliderA.position.y - colliderB.position.y - colliderB.size.y;

    if(d1x > 0.0f || d1y > 0.0f)
        return true;
    if(d2x > 0.0f || d2y > 0.0f)
        return false;

    return true;
}