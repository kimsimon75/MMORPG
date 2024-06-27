#pragma once
#include "·»´õ.h"
#include <string.h>

class Unit
{
protected:

	int current_hp;
	int current_mp;
	int attack;
	int intelligence;
	int agility;
	int armor;
	int restore;

	int max_hp;
	int max_mp;

	bool poison = false;
	bool ignite = false;
public:
	Unit(int hp, int mp, int attack, int intelligence, int agility, int armor, int restore)
	{
			this->max_hp = hp;
			current_hp = max_hp;
			this->max_mp = mp;
			current_mp = 0;
			this->attack = attack;
			this->intelligence = intelligence;
			this->agility = agility;
			this->armor = armor;
			this->restore = restore;
	}
	void basic_Attack(Unit* target)
	{
		int damage = attack - target->armor;
		if (damage < 0)
			damage = 0;
		target->current_hp -= (damage);
	}

	void Restoring()
	{
		current_hp += restore;
		if (current_hp > max_hp)
			current_hp = max_hp;
	}
};

class Player : public Unit
{
private :
	int playerNumber;
public:
	Player(int hp, int mp, int attack, int intelligence, int agility, int armor, int restore,int playerNumber) : Unit(hp, mp, attack, intelligence, agility, armor, restore)
	{
		this->playerNumber = playerNumber;
	}

	 void SetPN(int a)
	{
		playerNumber = a;
	}


};


class Enemy : public Unit
{
public:
	Enemy(int hp, int mp, int attack, int intelligence, int agility, int armor, int restore) : Unit(hp, mp, attack, intelligence, agility, armor, restore) {}
	int returnHP()
	{
		return current_hp;
	}
};


const int playerInfo[4][7] = { 
	300,0,30,0,30,50,30,
	150,150,10,50,50,30,50,
	200, 30, 20, 10, 80, 20, 0,
	10,200,0,200,200,0,0 };

const int enemyInfo[2][7] = {
	100, 50, 0, 200, 10, 20, 0,
	200, 0, 30, 0, 80, 10, 0,
};

