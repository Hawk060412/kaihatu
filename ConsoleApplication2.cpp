#include <iostream>
#include "EnemyFactory.h"
#include "Enemy.h"

int main() {

	int num;
	num = std::rand() % 4 + 1; // 1から4のランダムな整数を生成
    

	Enemy* enemy = EnemyFactory::CreateEnemy(1);
	std::cout << enemy->Data.Name << "EXP:" << enemy->Data.EXP << "Gold:" << enemy->Data.Gold << std::endl;
	

	delete enemy;

	return 0;

}