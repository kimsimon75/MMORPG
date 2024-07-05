#ifndef _UNITMANAGER_
#define _UNITMANAGER_
#include "플레이어.h"
#include "적.h"

class UnitManager
{
private:
	static UnitManager* p;
public:
	static UnitManager* Get();
private:
	Player* player = nullptr;
	Enemy* enemy = nullptr;
public:
	void SetPlayer(int id);

	Player& returnPlayer();

	void NextRound(Player& clone);

	void SetEnemy(int round);
	Enemy& returnEnemy();
	
};
#endif