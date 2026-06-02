#include <iostream>
#include <iomanip>
#include <random>
#include <algorithm>
#include "EnemyFactory.h"
#include "Enemy.h"
#include "player.h"

int main() {
	const int numEnemies = 4;

	// 乱数エンジン（非決定的シード）
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<int> dist(1, 4);
	std::uniform_real_distribution<float> dist01(0.0f, 100.0f);

	player hero("勇者", 120, 25, 8, 12);

	std::cout << "=== バトル開始 ===" << std::endl;
	std::cout << "プレイヤー: " << hero.Name << " HP:" << hero.HP << " ATK:" << hero.ATK << " DEF:" << hero.DEF << " SPD:" << hero.SPD << std::endl;	

	for (int i = 0; i < numEnemies; ++i) {
		int id = dist(rng);
		Enemy* enemy = EnemyFactory::CreateEnemy(id);
		if (!enemy) {
			std::cerr << "Enemy ID " << id << " が見つかりませんでした。" << std::endl;
			continue;
		}

		std::cout << "\n--- 敵出現: " << enemy->Data.Name << " (ID:" << id << ") HP:" << enemy->Data.HP << " ATK:" << enemy->Data.ATK << " DEF:" << enemy->Data.DEF << " SPD:" << enemy->Data.SPD << " CritRate:" << std::fixed << std::setprecision(2) << enemy->Data.CriticalRate << "%) ---" << std::endl;

		// 戦闘用に敵HPをコピー（Enemy.Data はインスタンス固有）
		int enemyHP = enemy->Data.HP;

		int turn = 1;
		while (hero.HP > 0 && enemyHP > 0) {
			std::cout << "[ターン " << turn << "]" << std::endl;

			// どちらが先行するか（SPDが高い方、同値ならランダム）
			bool heroFirst = false;
			if (hero.SPD > enemy->Data.SPD) heroFirst = true;
			else if (hero.SPD < enemy->Data.SPD) heroFirst = false;
			else heroFirst = (dist01(rng) < 50.0f);

			auto doAttack = [&](const std::string& attackerName, int atk, int def, float critRate, int& targetHP) {
				bool isCrit = (dist01(rng) < critRate);
				int damage = std::max(1, atk - def);
				if (isCrit) damage *= 2;
				targetHP -= damage;
				if (targetHP < 0) targetHP = 0;
				std::cout << attackerName << " の攻撃! ダメージ:" << damage << (isCrit ? " (クリティカル)" : "") << " 残HP:" << targetHP << std::endl;
			};

			if (heroFirst) {
				doAttack(hero.Name, hero.ATK, enemy->Data.DEF, 0.0f /*プレイヤーのクリ率固定0*/ , enemyHP);
				if (enemyHP <= 0) break;
				doAttack(enemy->Data.Name, enemy->Data.ATK, hero.DEF, enemy->Data.CriticalRate, hero.HP);
			} else {
				doAttack(enemy->Data.Name, enemy->Data.ATK, hero.DEF, enemy->Data.CriticalRate, hero.HP);
				if (hero.HP <= 0) break;
				doAttack(hero.Name, hero.ATK, enemy->Data.DEF, 0.0f, enemyHP);
			}

			++turn;
		}

		if (hero.HP <= 0) {
			std::cout << "\n>> " << hero.Name << " は倒れた... ゲームオーバー" << std::endl;
			delete enemy;
			break;
		} else {
			std::cout << "\n>> " << enemy->Data.Name << " を撃破した！" << std::endl;
			// 敵撃破後は報酬などを表示（必要なら拡張）
		}

		delete enemy;
	}

	if (hero.HP > 0) {
		std::cout << "\n=== 全ての戦闘が終了しました ===" << std::endl;
		std::cout << hero.Name << " の残りHP: " << hero.HP << std::endl;
	}

	return 0;
}