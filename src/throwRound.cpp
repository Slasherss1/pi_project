#include "throwRound.h"
#include "drinkMeter.h"
#include "masher.h"
#include "utils.h"
#include <raylib.h>
#include <string>

void ThrowRound::load() {
    bg = LoadTexture("assets/concrete.png");
    drinkMeter.sipSize = 0.1f;

    target.texture = LoadTexture("assets/cel.png");
    target.mass = 0.05; // gram
    target.colliderRadius = 23.0; // pixels
    target.crossSection = 0.01; // m^2
    target.safeZone.radius = 40.0;
    target.decay = 15.0;
    
    ap.position = {400.0, 500.0};
    ap.texture = LoadTexture("assets/zgniot.png");
    ap.proj_pp = &proj;
    
    character.texture = LoadTexture("assets/miniziel1.png");
}

void ThrowRound::unload() {
    UnloadTexture(bg);
    delete drinkMash;
    drinkMash = nullptr;
    UnloadTexture(target.texture);
    UnloadTexture(ap.texture);
}

void ThrowRound::loop() {
    if (proj != nullptr) {
        proj->Tick();
        col.handleCollision(&target, proj);
    }
    ap.Tick();
    target.Tick();
    character.Tick();

    if (target.isHit()) {
        if (!drinkMash) {
            drinkMash = new Masher();
            drinkMash->text = "Pij!";
        }
    } else {
    }
    
    if (drinkMash) {
        drinkMash->tick();
        
        if (drinkMash->isPressed()) {
            drinkMeter.sip();
        }

        if (drinkMeter.currentLevel < 1e-9) {
            delete drinkMash;
            drinkMash = nullptr;
        }
    }

    BeginDrawing();
    DrawBackground(bg);
    target.Draw();
    if (proj != nullptr) {
        proj->Draw();
    }
    character.Draw();
    ap.Draw();
    drinkMeter.draw();
    if (drinkMash) drinkMash->draw();

    EndDrawing();
}
