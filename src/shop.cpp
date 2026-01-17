#include "shop.h"
#include "utils.h"
#include "town_map.h"

static const char* SHOP_NAME = "Studenciak";
static const char* SHOP_INSTRUCTION = "Nacisnij SPACJE, aby wyjsc";
static const char* WALLET_STATUS = "Portfel: 2137zl";

void Shop::load() {
	shopInterior = LoadTexture("assets/studenciak.png");
	beers = {
		LoadTexture("assets/carlsberg.png"),
		LoadTexture("assets/cel.png"),
		LoadTexture("assets/zywiec.png"),
		LoadTexture("assets/zywiec_ciemne.png"),
		LoadTexture("assets/tyskie.png"),
		LoadTexture("assets/perla_export.png")
	};
}

void Shop::unload() {
	UnloadTexture(shopInterior);
}

void Shop::loop() {
	if (IsKeyDown(KEY_SPACE)) {
		LevelManager::changeLevel(new TownMap());
	}

	BeginDrawing();

	DrawTexture(shopInterior, 0, 0, WHITE);
	DrawText(SHOP_NAME, GetCenteredX(SHOP_NAME, 70), 20, 70, YELLOW);
	DrawText(SHOP_INSTRUCTION, GetScreenWidth() - MeasureText(SHOP_INSTRUCTION, 20) - 2, GetScreenHeight() - 22, 20, WHITE);
	DrawText(WALLET_STATUS, GetCenteredX(WALLET_STATUS, 20), 90, 20, WHITE);
	DrawText("Na razie nic tu nie ma\nProsze przyjsc pozniej :)", GetCenteredX("Na razie nic tu nie ma\nProsze przyjsc pozniej :)", 40), GetScreenHeight() / 2 - 80, 40, SKYBLUE);

	EndDrawing();
}

void Shop::showBeersWithInfo() {
	// Implementation for showing beers with info (not provided in the original snippet)
}