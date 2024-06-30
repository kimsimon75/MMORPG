#ifndef _UNIT_
#define _UNIT_
#include "РЏДж.h"
#endif


static bool gameover = false;

class Player : public Unit
{
private:

	int playerNumber;
	int damageUpCool=0;
	friend class Enemy;
public:
	Player(int hp, int mp, int attack, int intelligence, int agility, int armor, int restore, int id) : Unit(hp, mp, attack, intelligence, agility, armor, restore)
	{
		this->playerNumber = id;
	}

	void basic_Attack(class Unit& target);

	int PN()
	{
		return playerNumber;
	}

	void SetPN(int& id)
	{
		playerNumber = id;
	}

	void DamageUp(Unit& target)
	{
		damageUpCool = 5;
		current_hp -= 50;
		if (current_hp <= 0)
			gameover = true;
	}
	int& ShowBuff()
	{
		return damageUpCool;
	}

	void SetDamage(float rank)
	{
		attack = basic_damage * rank;
	}

	void DoubleAttack(Unit& target)
	{
		std::random_device rd;

		std::mt19937 gen(rd());

		std::uniform_int_distribution<int> dis(0, 99);

		if (dis(gen) < 60)
		{
			basic_Attack(target);
			basic_Attack(target);
		}
	}
};


