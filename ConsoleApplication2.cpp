#include <iostream>
#include <iomanip>
#include <random>
#include "EnemyFactory.h"
#include "Enemy.h"

int main() {
	const int numEnemies = 4;

		// 乱数エンジン（非決定的シード）
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<int> dist(1, 4);

	int totalHP = 0;
	int totalATK = 0;
	int generatedCount = 0;

	for (int i = 0; i < numEnemies; ++i) {
		int id = dist(rng);
		Enemy* enemy = EnemyFactory::CreateEnemy(id);
		if (!enemy) {
			std::cerr << "Enemy ID " << id << " が見つかりませんでした。" << std::endl;
			continue;
		}

		std::cout << enemy->Data.Name
				  << " (ID:" << id << ")"
				  << " HP:" << enemy->Data.HP
				  << " ATK:" << enemy->Data.ATK
				  << " DEF:" << enemy->Data.DEF
				  << " SPD:" << enemy->Data.SPD
				  << " EXP:" << enemy->Data.EXP
				  << " Gold:" << enemy->Data.Gold
				  << " CritRate:" << std::fixed << std::setprecision(2) << enemy->Data.CriticalRate << "%"
				  << std::endl;

		totalHP += enemy->Data.HP;
		totalATK += enemy->Data.ATK;
		++generatedCount;

		delete enemy;
	}

	if (generatedCount > 0) {
		double avgATK = static_cast<double>(totalATK) / generatedCount;
		std::cout << "生成数: " << generatedCount << std::endl;
		std::cout << "HP合計: " << totalHP << std::endl;
		std::cout << "平均ATK: " << std::fixed << std::setprecision(2) << avgATK << std::endl;
	} else {
		std::cout << "敵が一体も生成されませんでした。" << std::endl;
	}

	return 0;
}