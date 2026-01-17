#pragma once
#include <string>
#include <vector>
#include <raylib.h>

enum GameDifficulty { EASY, HARD };

// klasa typu singleton
class InventoryManager {
public:
    static InventoryManager& getInstance() {
        static InventoryManager instance;
        return instance;
    }

    InventoryManager(const InventoryManager&) = delete;
    void operator=(const InventoryManager&) = delete;

	void changeDifficulty(GameDifficulty diff);

    // TODO: zaimplementowac klase "piwo" zawierajaca nazwe, zdjecie i perki
    void addBeer(const std::string& beer);
	bool removeBeer(const std::string& beer);

	void addMoney(int amount);
	void removeMoney(int amount);

	int getWallet() const;
    std::vector<std::string> getBeers() const;

	bool saveInventory(const std::string& filename) const;
	bool loadInventory(const std::string& filename);

private:
    InventoryManager() {}

    int wallet;
    std::vector<std::string> beers;
    GameDifficulty difficulty;
};