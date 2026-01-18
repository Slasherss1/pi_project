#include "inventory.h"
#include "inventory_manager.h"
#include "utils.h"
#include "town_map.h"

static const char* INV_NAME = "Ekwipunek";
static const char* INV_INSTRUCTION = "Nacisnij SPACJE, aby wyjsc";

void Inventory::load() {
	inventoryBackground = LoadTexture("assets/inventorytlo.png");
	beers = { {
		{LoadTexture("assets/carlsberg.png"),		"Carlsberg"},
		{LoadTexture("assets/cel.png"),				"Zubr"},
		{LoadTexture("assets/zywiec.png"),			"Zywiec"},
		{LoadTexture("assets/zywiec_ciemne.png"),	"Zywiec ciemne"},
		{LoadTexture("assets/tyskie.png"),			"Tyskie"},
		{LoadTexture("assets/perla_export.png"),	"Perla export"}
	} };
}

void Inventory::unload() {
	UnloadTexture(inventoryBackground);
	for (const auto& beer : beers) {
		UnloadTexture(beer.first);
	}
}

void Inventory::loop() {
	InventoryManager& inventory = InventoryManager::getInstance();
	std::string wallet = "Portfel: " + std::to_string(InventoryManager::getInstance().getWallet()) + "zl";

	if (IsKeyDown(KEY_SPACE)) {
		LevelManager::changeLevel(new TownMap());
		return;
	}

	BeginDrawing();

	DrawTexture(inventoryBackground, 0, 0, WHITE);
	DrawText(INV_NAME, GetCenteredX(INV_NAME, 70), 20, 70, YELLOW);
	DrawText(INV_INSTRUCTION, GetScreenWidth() - MeasureText(INV_INSTRUCTION, 20) - 2, GetScreenHeight() - 22, 20, WHITE);
	DrawText(wallet.c_str(), GetCenteredX(wallet.c_str(), 20), 90, 20, WHITE);

	showBeersInfo(beers, false);

	EndDrawing();
}