#include "physObj.h"
#include "safeZone.h"

class Target : public PhysicsObj {
    public:
        SafeZone safeZone;
        void Draw() override;
};