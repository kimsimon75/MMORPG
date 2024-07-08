#include "unitmanager.h"

UnitManager* UnitManager::p = nullptr;

 UnitManager* UnitManager::Get()
{
	if (p == nullptr)
	{
		p = new UnitManager;
	}
	return p;
}

 void UnitManager::SetPlayer(int id) {
	if (player != nullptr)
	{
		delete player;
		player = nullptr;
	}
	player = new Player(playerInfo[id - 1][0], playerInfo[id - 1][1], playerInfo[id - 1][2], playerInfo[id - 1][3], playerInfo[id - 1][4], playerInfo[id - 1][5], playerInfo[id - 1][6], id);
}

 Player& UnitManager::returnPlayer()
{
	return *player;
}

 void UnitManager::NextRound(Player& clone)
{

	player = new Player(clone);
	delete& clone;
}

 void UnitManager::SetEnemy(int round)
{
	if (enemy != nullptr)
	{
		delete enemy;
		enemy = nullptr;
	}
	enemy = new Enemy(enemyInfo[round][0], enemyInfo[round][1], enemyInfo[round][2], enemyInfo[round][3], enemyInfo[round][4], enemyInfo[round][5], enemyInfo[round][6]);
}

 Enemy& UnitManager::returnEnemy()
{
	return *enemy;
}
