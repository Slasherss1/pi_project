#pragma once
#include <raylib.h>

bool TextButton(const char* text, Vector2 pos, int fontSize, Color normal, Color hover);
float GetCenteredX(const char* text, int fontSize);
void DrawBackground(Texture2D menuTexture);