#include <raylib.h>

class PhysicsObj {
    protected:
        Vector2 position = {0.0f, 0.0f};
        Vector2 velocity = {0.0f, 0.00f};

    public:
        virtual ~PhysicsObj();
        Texture2D texture;
        void Tick();
        virtual void Draw();
};