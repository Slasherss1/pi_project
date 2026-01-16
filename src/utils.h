#pragma once
#include <raylib.h>
#include <string>

bool TextButton(const char* text, Vector2 pos, int fontSize, Color normal, Color hover);
bool TextureButton(Texture2D texture, Vector2 position, Color tint);
float GetCenteredX(const char* text, int fontSize);
float GetCenteredXInBounds(const char* text, int fontSize, float left, float right);
void DrawBackground(Texture2D menuTexture);

std::string GetKeycodePrintableName(KeyboardKey key);