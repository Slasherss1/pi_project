#include <raylib.h>
#include "physObj.h"

void PhysicsObj::Tick() {
    this->position.x += GetFrameTime() * this->velocity.x;
    this->position.y += GetFrameTime() * this->velocity.y;
    // DrawRectangle(position.x, position.y, 10, 10, BLACK);
}

void PhysicsObj::Draw() { }

PhysicsObj::~PhysicsObj() {

}
