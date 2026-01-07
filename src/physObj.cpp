#include <raylib.h>
#include "physObj.h"

void PhysicsObj::Tick() {
    this->velocity.x += (GetFrameTime() * this->forceDir.x) / this->mass;
    this->velocity.y += (GetFrameTime() * this->forceDir.y) / this->mass;
    // drag
    this->velocity.x -= (GetFrameTime() * this->crossSection * this->velocity.x * this->velocity.x) / this->mass;
    this->velocity.y -= (GetFrameTime() * this->crossSection * this->velocity.y * this->velocity.y) / this->mass;

    this->position.x += GetFrameTime() * this->velocity.x;
    this->position.y += GetFrameTime() * this->velocity.y;
}

void PhysicsObj::Draw() { }

PhysicsObj::~PhysicsObj() {

}
