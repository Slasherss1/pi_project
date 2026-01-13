#include "utils.h"

bool TextButton(const char* text, Vector2 pos, int fontSize, Color normal, Color hover) {
    Vector2 size = MeasureTextEx(GetFontDefault(), text, fontSize, 1);
    Rectangle rec = { pos.x, pos.y, size.x, size.y };

    bool isHovered = CheckCollisionPointRec(GetMousePosition(), rec);
    DrawText(text, pos.x, pos.y, fontSize, isHovered ? hover : normal);

    return isHovered && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}

float GetCenteredX(const char* text, int fontSize) {
    int textWidth = MeasureText(text, fontSize);
    return (GetScreenWidth() - textWidth) / 2.0f;
}

void DrawBackground(Texture2D texture) {
    DrawTexturePro(
        texture,
        {0, 0, (float) texture.width, (float) texture.height},
        {0, 0, (float) GetScreenWidth(), (float) GetScreenHeight()},
        {0, 0},
        0.0f,
        WHITE
    );
}
