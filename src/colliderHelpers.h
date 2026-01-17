#pragma once

#include "physObj.h"
class CollideAndBounce {
    private:
        bool isColliding = false;
    public:
      void handleCollision(PhysicsObj * obj1, PhysicsObj * obj2);
};