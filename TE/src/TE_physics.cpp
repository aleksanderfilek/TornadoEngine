#include"TE_physics.hpp"

bool BoxCollision2D(const BoxCollider2D &colliderA, const BoxCollider2D &colliderB){
    float d1x = colliderB.position.x - colliderA.position.x - colliderA.size.x;
    float d1y = colliderB.position.y - colliderA.position.y - colliderA.size.y;
    float d2x = colliderA.position.x - colliderB.position.x - colliderB.size.x;
    float d2y = colliderA.position.y - colliderB.position.y - colliderB.size.y;

    if(d1x > 0.0f || d1y > 0.0f)
        return false;
    if(d2x > 0.0f || d2y > 0.0f)
        return false;

    return true;
}

bool CircleCollision2D(const CircleCollider2D &colliderA, const CircleCollider2D &colliderB){
    float dx = colliderA.position.x - colliderB.position.x;
    dx *= dx;
    float dy = colliderA.position.y - colliderB.position.y;
    dy *= dy;
    float r = colliderA.radius + colliderB.radius;
    r *= r;

    if(dx + dy <= r)
        return true;

    return false;
}

bool Box_CircleCollision2D(const BoxCollider2D &colliderA, const CircleCollider2D &colliderB){
    float vertX = colliderB.position.x;
    float vertY = colliderB.position.y;

    if(colliderB.position.x < colliderA.position.x) vertX = colliderA.position.x;
    else if(colliderB.position.x > colliderA.position.x + colliderA.size.x) vertX = colliderA.position.x + colliderA.size.x;

    if(colliderB.position.y < colliderA.position.y) vertY = colliderA.position.y;
    else if(colliderB.position.y > colliderA.position.y + colliderA.size.y) vertY = colliderA.position.y + colliderA.size.y;

    float distX = colliderB.position.x - vertX;
    vertX *= vertX;
    float distY = colliderB.position.y - vertY;
    vertY *= vertY;

    if(distX + distY <= colliderB.radius * colliderB.radius )
        return true;

    return true;
}