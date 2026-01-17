#include "inventory_manager.h"
#include <sstream>
#include <cstring>

void InventoryManager::setDifficulty(GameDifficulty diff) {
	difficulty = diff;
}

void InventoryManager::addBeer(const std::string& beer) {
	beers.push_back(beer);
}

bool InventoryManager::removeBeer(const std::string& beer) {
	auto it = std::find(beers.begin(), beers.end(), beer);
	if (it != beers.end()) {
		beers.erase(it);
		return true;
	}
	return false;
}

void InventoryManager::addMoney(int amount) {
	wallet += amount;
}

void InventoryManager::removeMoney(int amount) {
	wallet -= amount;
}

int InventoryManager::getWallet() const {
	return wallet;
}

std::vector<std::string> InventoryManager::getBeers() const {
	return beers;
}

GameDifficulty InventoryManager::getDifficulty() const {
	return difficulty;
}

bool InventoryManager::saveInventory(const std::string& filename) const {
	// Format zapisywanych danych: difficulty|wallet|beer1;beer2;beer3...
	std::ostringstream oss;
	oss << static_cast<int>(difficulty) << "|" << wallet << "|";
	
	for (int i = 0; i < beers.size(); i++) {
		oss << beers[i];
		if (i < beers.size() - 1) oss << ";";
	}
	
	std::string data = oss.str();
	
	int compDataSize = 0;
	unsigned char* compData = CompressData(
		reinterpret_cast<const unsigned char*>(data.c_str()), 
		data.size(), 
		&compDataSize
	);
	
	if (compData == nullptr) return false;
	
	bool success = SaveFileData(filename.c_str(), compData, compDataSize);	
	MemFree(compData);

	return success;
}

bool InventoryManager::loadInventory(const std::string& filename) {
	int compDataSize = 0;
	unsigned char* compData = LoadFileData(filename.c_str(), &compDataSize);
	
	if (compData == nullptr) return false;
	
	int decompDataSize = 0;
	unsigned char* decompData = DecompressData(compData, compDataSize, &decompDataSize);
	
	UnloadFileData(compData);
	
	if (decompData == nullptr) return false;
	
	std::string data(reinterpret_cast<char*>(decompData), decompDataSize);
	MemFree(decompData);
	
	std::istringstream iss(data);
	std::string walletStr, diffStr, beersStr;
	
	if (!std::getline(iss, diffStr, '|')) return false;
	if (!std::getline(iss, walletStr, '|')) return false;
	std::getline(iss, beersStr);
	
	wallet = std::stoi(walletStr);
	difficulty = static_cast<GameDifficulty>(std::stoi(diffStr));
	
	beers.clear();
	if (!beersStr.empty()) {
		std::istringstream beersStream(beersStr);
		std::string beer;
		while (std::getline(beersStream, beer, ';')) {
			beers.push_back(beer);
		}
	}
	
	return true;
}

