#pragma once
#ifndef _UNIT_
#define _UNIT_
#include "unit.h"
#endif

static bool gameover = false;

class Player : public Unit
{
private:

	int playerNumber;
	int damageUpCool=0;
	int enemys = false;
	int gameRound = 0;

	int temporaryHP=0;
	int temporaryMP=0;
	int temporaryAttack = 0;
	int temporaryIntelligence = 0;
	int temporaryAgility = 0;
	int temporaryArmor = 0;
	int temporaryRestore = 0;

	friend class Enemy;
public:
	Player(int hp, int mp, int attack, int intelligence, int agility, int armor, int restore, int id);

	Player(Player& player);

	int PN();

	void SetPN(int& id);

	void SetAbility(const char* item, const char* weapon);

	void BuffRemove();

	int& GameRound();

	pair<bool, int> basic_Attack(class Unit& target);

	pair<bool, int> DamageUp(Unit& target);

	pair<bool, int> DoubleAttack(Unit& target);

	pair<bool, int> Enemy_s_(Unit& target);

	pair<bool, int> PoisonAttack(Unit& target);

	pair<bool, int> ignite(Unit& target);

	pair<bool, int> ShieldBash(Unit& target);

	pair<bool, int> Bite(Unit& target);
};