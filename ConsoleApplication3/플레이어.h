#pragma once
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
	int enemys = false;
	int gameRound = 0;
	friend class Enemy;
public:
	Player(int hp, int mp, int attack, int intelligence, int agility, int armor, int restore, int id) : Unit(hp, mp, attack, intelligence, agility, armor, restore)
	{
		this->playerNumber = id;
		this->current_mp = max_mp;
	}

	Player(Player& player) : Unit(player.max_hp, player.max_mp, player.basic_damage, player.basic_intelligence, player.agility, player.armor, player.restore)
	{
		playerNumber = player.playerNumber;
		if (player.playerNumber == 3)
		{
			basic_damage = player.basic_damage; 
			attack = player.attack;
		}
		if (player.playerNumber == 4)
		{
			basic_intelligence = player.basic_intelligence;
			intelligence = player.intelligence;
		}
	}

	int PN()
	{
		return playerNumber;
	}

	void SetPN(int& id)
	{
		playerNumber = id;
	}
	
	int& ShowBuff()
	{
		return damageUpCool;
	}

	void SetDamage(float rank)
	{
		attack = basic_damage * rank;
	}
	int& GameRound()
	{
		return gameRound;
	}

	pair<bool, int> basic_Attack(class Unit& target);

	pair<bool, int> DamageUp(Unit& target)
	{
		int hp = 50;
		if (alertCount == 0)
			return make_pair(0, hp);
		else if(alertCount == -1)
		{
			damageUpCool = 5;
			current_hp -= hp;
			pre_hp = current_hp;
		}
		return make_pair(0,0);
	}

	pair<bool, int> DoubleAttack(Unit& target)
	{
		std::random_device rd;

		std::mt19937 gen(rd());

		std::uniform_int_distribution<int> dis(0, 99);

		if (dis(gen) < 60)
		{
			basic_Attack(target);
			basic_Attack(target);
		}
		return make_pair(0, 0);
	}

	pair<bool, int> Enemy_s_(Unit& target)
	{
		if(!enemys)
		{
			int mana = 50;
			if (alertCount == 0)
				return make_pair(1, mana);
			if(alertCount == -1)
			{
				switch (gameRound)
				{
				case 0:
					Unit::PoisonAttack(target);
					break;
				case 1:
					Unit::DamageUp();
	  	 			 break;
				}
				current_mp -= mana;
			}
			enemys = true;
		}
	}

	pair<bool, int> PoisonAttack(Unit& target)
	{
		int mana = 30;
		if(alertCount==0)
			return make_pair(1, mana);
		else if(alertCount == -1)
		{
			target.poison_time = 2;
			target.poison_damage = (10 + (float)intelligence * 0.2) * (1 + (float)agility * 0.03);
			current_mp -= mana;
		}
	}
	pair<bool, int> ignite(Unit& target)
	{
		int mana = 30;
		if (alertCount == 0)
			return make_pair(1, mana);
		else if (alertCount == -1)
		{
			target.ignite_time = 2 * (1 + 0.01 * intelligence);
			target.ignite_damage = 30;
		}
	}
};