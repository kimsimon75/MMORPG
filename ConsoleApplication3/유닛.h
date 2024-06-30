#pragma once
#include <random>

class Unit
{
protected:

	int current_hp = 1;
	int current_mp = 2;
	int attack = 3;
	int intelligence = 4;
	int agility = 5;
	int armor = 6;
	int restore = 7;

	int max_hp = 8;
	int max_mp = 9;

	int basic_damage = 10;
	short poison_time = 11;
	short poison_damage = 12;
	bool ignite = false;
	int stun = 0;
	bool turn = false;
	int pre_hp;

	friend class Enemy;
	friend class Player;
public:

	bool poison = false;

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
		this->basic_damage = attack;
		pre_hp = hp;
	}
	int& returnHP()
	{
		return current_hp;
	}
	int& ReturnMP()
	{
		return current_mp;
	}

	bool GetDamage(bool test)
	{
		if (current_hp != pre_hp)
		{
			if(test == true)
				pre_hp = current_hp;
			return true;
		}
		else
			return false;
	}

	int& StunTime()
	{
		return stun;
	}

	void Restoring()
	{
		current_hp += restore;
		if (current_hp > max_hp)
			current_hp = max_hp;
	}

	void ManaCharge()
	{
		current_mp += (intelligence + max_mp) / 10;
		if (current_mp > max_mp)
			current_mp = max_mp;
	}

	void PoisonAttack(Unit& target)
	{
		target.poison = true;
		target.poison_time = 2;
		target.poison_damage = (10 + (float)intelligence * 0.1) * (1 + (float)agility * 0.07);
	}

	void GetPoison()
	{
		current_hp -= poison_damage;
		--poison_time;
		if (poison_time <= 0)
			poison = false;
	}

	int PoisonTime()
	{
		return poison_time;
	}

	void DamageUp()
	{
		attack += basic_damage * 0.5;
	}

	void basic_Attack(Unit& target)
	{
		int damage = attack - target.armor;
		if (damage < 0)
			damage = 0;
		target.current_hp -= (damage);

	}


	void Rush(Unit& target)
	{
		int damage = 1.5 * attack - target.armor;
		if (damage < 0)
			damage = 0;
		target.current_hp -= (damage);
		stun = 1;
	}

	bool& TurnReturn()
	{
		return turn;
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

