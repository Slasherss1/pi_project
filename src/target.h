#include "physObj.h"

typedef struct SafeZone {
    Vector2 position;
    float radius;
} SafeZone;

class Target : public PhysicsObj {
    public:
        Target(Vector2);
        SafeZone safeZone;
        void Draw() override;
};
