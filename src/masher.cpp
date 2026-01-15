#include "masher.h"
#include "utils.h"
#include <raylib.h>
#include <string>

#define getNinSeq(n) this->sequence[(n) % this->sequence.size()]

void Masher::tick() {
    keyName = GetKeycodePrintableName(getNinSeq(count));
    if (IsKeyPressed(getNinSeq(count))) {
        count++;
        pressed = true;
    } else {
        pressed = false;
    }
}

void Masher::draw() {
    DrawText(this->text.c_str(), GetCenteredX(this->text.c_str(), 42), 200, 42, WHITE);
    DrawText(keyName.c_str(), GetCenteredX(keyName.c_str(), 32), 300, 32, YELLOW);
}

bool Masher::isPressed() {
    return this->pressed;
}