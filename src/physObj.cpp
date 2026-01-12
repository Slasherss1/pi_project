#include <raylib.h>
#include <raymath.h>
#include "physObj.h"

void PhysicsObj::Tick() {
    this->velocity.x += (GetFrameTime() * this->forceDir.x) / this->mass;
    this->velocity.y += (GetFrameTime() * this->forceDir.y) / this->mass;
    // drag
    this->velocity.x -= (GetFrameTime() * (this->crossSection * this->velocity.x * fabs(this->velocity.x) / 2)) / this->mass;
    this->velocity.y -= (GetFrameTime() * (this->crossSection * this->velocity.y * fabs(this->velocity.y) / 2)) / this->mass;

    // decay
    float fLen = Vector2Length(this->forceDir);
    if (fLen > 0.0f) {
        float newLen = fLen - this->decay * GetFrameTime();
        if (newLen <= 0.0f) this->forceDir = Vector2Zero();
        else this->forceDir = Vector2Scale(Vector2Normalize(this->forceDir), newLen);
    }

    this->position.x += GetFrameTime() * this->velocity.x;
    this->position.y += GetFrameTime() * this->velocity.y;
}

void PhysicsObj::Draw() { }

PhysicsObj::~PhysicsObj() {

}
