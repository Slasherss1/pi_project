#include "colliderHelpers.h"
#include <raymath.h>

void CollideAndBounce::handleCollision(PhysicsObj * obj1, PhysicsObj * obj2) {
    if (obj1 == nullptr || obj2 == nullptr) return;
    if (CheckCollisionCircles(obj1->position, obj1->coliderRadius, obj2->position, obj2->coliderRadius)) {
        if (isColliding) return;
        isColliding = true;
    } else {
        isColliding = false;
        return;
    }
    const Vector2 angleDir = Vector2Negate(Vector2Subtract(obj2->position, obj1->position));
    const Vector2 impact = Vector2Add(obj2->forceDir, obj1->forceDir);
    const Vector2 totalVelocity = Vector2Add(obj2->velocity, obj1->velocity);
    const float totalMass = obj2->mass + obj1->mass;
    const float angle = Vector2Angle(angleDir, obj2->forceDir);
    const float nangle = angle - PI;
    obj1->velocity = Vector2Rotate(Vector2Scale(totalVelocity, obj2->mass / totalMass), angle);
    obj2->velocity = Vector2Rotate(Vector2Scale(totalVelocity, obj1->mass / totalMass), nangle);
    obj1->forceDir = Vector2Rotate(Vector2Scale(impact, obj2->mass / totalMass), angle);
    obj2->forceDir = Vector2Rotate(Vector2Scale(impact, obj1->mass / totalMass), nangle);
}
