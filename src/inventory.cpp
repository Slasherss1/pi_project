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

	// TODO: mozna przeniesc do utils.h
	const int BEER_PRICE = 1;
	const int BEERS_PER_ROW = 3;
	const int START_Y = 150;
	const int ROW_SPACING = 250;
	const int BEER_SPACING = 800 / (BEERS_PER_ROW + 1);

	for (int i = 0; i < beers.size(); i++) {
		int row = i / BEERS_PER_ROW;
		int col = i % BEERS_PER_ROW;

		int x = BEER_SPACING * (col + 1) - beers[i].first.width / 2;
		int y = START_Y + row * ROW_SPACING;

		DrawTexture(beers[i].first, x, y, WHITE);

		std::string beerName = beers[i].second + " x" + std::to_string(inventory.countBeer(beers[i].second));
		int nameWidth = MeasureText(beerName.c_str(), 18);
		int nameX = BEER_SPACING * (col + 1) - nameWidth / 2;
		int nameY = y + beers[i].first.height + 5;
		DrawText(beerName.c_str(), nameX, nameY, 18, WHITE);
	}

	EndDrawing();
}