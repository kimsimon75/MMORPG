#pragma once
#include "플레이어.h"
#include "적.h"

class UnitManager
{
private:
	static UnitManager* p;
public:
	static UnitManager* Get()
	{
		if (p == nullptr)
		{
			p = new UnitManager;
		}
		return p;
	}
private:
	Player* player = nullptr;
	Enemy* enemy = nullptr;
public:
	void SetPlayer(int id) {
		if (player != nullptr)
		{
			delete player;
			player = nullptr;
		}
		player = new Player(playerInfo[id-1][0], playerInfo[id - 1][1], playerInfo[id - 1][2], playerInfo[id - 1][3], playerInfo[id - 1][4], playerInfo[id - 1][5], playerInfo[id - 1][6], id);
	}

	Player& returnPlayer()
	{
		return *player;
	}

	void SetEnemy(int round)
	{
		if (enemy != nullptr)
		{
			delete enemy;
			enemy = nullptr;
		}
		enemy = new Enemy(enemyInfo[round][0], enemyInfo[round][1], enemyInfo[round][2], enemyInfo[round][3], enemyInfo[round][4], enemyInfo[round][5], enemyInfo[round][6]);
	}
	Enemy& returnEnemy()
	{
		return *enemy;
	}
};

UnitManager* UnitManager::p = nullptr;