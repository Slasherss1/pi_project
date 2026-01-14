#include "utils.h"

bool TextButton(const char* text, Vector2 pos, int fontSize, Color normal, Color hover) {
    Vector2 size = MeasureTextEx(GetFontDefault(), text, fontSize, 1);
    Rectangle rec = { pos.x, pos.y, size.x, size.y };

    bool isHovered = CheckCollisionPointRec(GetMousePosition(), rec);
    DrawText(text, pos.x, pos.y, fontSize, isHovered ? hover : normal);

    return isHovered && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}

bool TextureButton(Texture2D texture, Vector2 position, Color tint) {
    Rectangle rect = { position.x, position.y, (float) texture.width, (float) texture.height };
    DrawTexture(texture, (int) position.x, (int) position.y, tint);
    return CheckCollisionPointRec(GetMousePosition(), rect) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}

bool DifficultyTextButton(const char* text, Vector2 pos, int fontSize, Color normal, Color hover) {
    Vector2 size = MeasureTextEx(GetFontDefault(), text, fontSize, 1);
    Rectangle rec = { pos.x, pos.y, size.x, size.y };

    bool isHovered = CheckCollisionPointRec(GetMousePosition(), rec);
    DrawText(text, pos.x, pos.y, fontSize, isHovered ? hover : normal);

    return isHovered && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}

float GetCenteredXInBounds(const char* text, int fontSize, float left, float right) {
    int textWidth = MeasureText(text, fontSize);
    float boundsWidth = right - left;
    return left + (boundsWidth - textWidth) / 2.0f;
}

float GetCenteredX(const char* text, int fontSize) {
    return GetCenteredXInBounds(text, fontSize, 0, GetScreenWidth());
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
