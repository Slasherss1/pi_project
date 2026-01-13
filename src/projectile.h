#include "physObj.h"

class Projectile : public PhysicsObj {
    public:
        void Draw() override;
};

class AimableProjectile {
    private:
        bool isAiming = false;
        bool isShot = false;
    public:
        Texture2D texture;
        Vector2 position = {0.0f, 0.0f};

        Projectile** proj_pp = nullptr;

        void Draw();
        void Tick();
        void Shoot(Vector2);
};