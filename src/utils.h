#pragma once
#include "beer_effect.h"
#include <raylib.h>
#include <string>
#include <unordered_map>

bool TextButton(const char* text, Vector2 pos, int fontSize, Color normal, Color hover);
bool TextureButton(Texture2D texture, Vector2 position, Color tint);

float GetCenteredX(const char* text, int fontSize);
float GetCenteredXInBounds(const char* text, int fontSize, float left, float right);

void DrawBackground(Texture2D menuTexture);

std::string GetKeycodePrintableName(KeyboardKey key);

std::unordered_map<std::string, Texture2D> loadBeerTextures();
void unloadBeerTextures(std::unordered_map<std::string, Texture2D>& beerTextures);
void showBeersInfo(std::unordered_map<std::string, Texture2D>& beerTextures, bool showPrice);

const BeerEffect* beerByNameHasEffect(const std::string& beerName, EffectType effectType);