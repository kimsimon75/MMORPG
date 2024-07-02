#pragma once
#include <vector>
#include <random>


using namespace std;




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
	int barrier = 10;

	int basic_damage = 10;
	int basic_intelligence = 0;
	int getDamage = 0;
	short poison_time = 0;
	short poison_damage = 12;
	int ignite_time = 0;
	int ignite_damage = 0;
	int stun = 0;
	int iced = 0;
	bool turn = false;
	bool sustained_DPS = false;
	int pre_hp;
	int barrierCool = 0;
	int intelUpCool = 0;

	int alertCount = 0;

	int attackPoint = 0;

	friend class Enemy;
	friend class Player;
public:

	Unit(int hp, int mp, int attack, int intelligence, int agility, int armor, int restore)
	{
		this->max_hp = hp;
		current_hp = max_hp;
		this->max_mp = mp;
		current_mp = max_mp;
		this->attack = attack;
		this->intelligence = intelligence;
		this->agility = agility;
		this->armor = armor;
		this->restore = restore;
		this->basic_damage = attack;
		this->basic_intelligence = intelligence;
		pre_hp = hp;
		barrier = 0;
	}
	int& ReturnHP()
	{
		return current_hp;
	}
	int& ReturnMP()
	{
		return current_mp;
	}
	int& SetAlertCount()
	{
		return alertCount;
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

	void GetPoison()
	{
		barrier -= poison_damage;
		if (barrier < 0)
		{
			current_hp += barrier;
			barrier = 0;
		}
		--poison_time;
	}

	int PoisonTime()
	{
		return poison_time;
	}

	void DamageUp()
	{
		attack += basic_damage * 0.5;
	}

	bool& TurnReturn()
	{
		return turn;
	}
	int& iced_time()
	{
		return iced;
	}

	int& BarrierCool()
	{
		return barrierCool;
 	}    

	int& BarrierSize()
	{
		return barrier;
	}

	int& IntelCool()
	{
		return intelUpCool;
	}

	void SetIntel(int rank)
	{
		intelligence = basic_intelligence + rank;
	}

	bool Sustained_DPS()
	{
		if (ignite_time || poison_time)
			return true;
		return false;
	}

	int& AP()
	{
		return attackPoint;
	}
	void APCharge()
	{
		attackPoint += 10 + agility * 0.05;
	}

	pair<bool, int> PoisonAttack(Unit& target)
	{
		target.poison_time = 2;
		target.poison_damage = (10 + (float)intelligence * 0.1) * (1 + (float)agility * 0.07);

		return make_pair(1, 30);
	}

	pair<bool, int> basic_Attack(Unit& target)
	{

		int damage = attack - target.armor;
		if (damage < 0)
			damage = 0;
		target.barrier -= damage;
		if (target.barrier < 0)
		{
			target.current_hp += target.barrier;
			target.barrier = 0;
		}
		return make_pair(0, 0);
	}

	pair<bool, int> Rush(Unit& target)
	{
		if(alertCount==0)
			return make_pair(0, 0);
		else if(alertCount==-1)
		{
			int damage = 1.5 * attack - target.armor;
			if (damage < 0)
				damage = 0;
			target.barrier -= damage;
			if (target.barrier < 0)
			{
				target.current_hp += target.barrier;
				target.barrier = 0;
			}
			stun = 2;
		}
	}

	pair<bool, int> fireball(Unit& target)
	{
		int mana = 20;
		
		if(alertCount==0)
			return make_pair(1, mana);
		else if(alertCount==-1)
		{
			int damage = 20 + intelligence * 0.1;
			if (damage < 0)
				damage = 0;
			target.barrier -= damage;
			if (target.barrier < 0)
			{
				target.current_hp += target.barrier;
				target.barrier = 0;
			}
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
			target.poison_time = 2;
			target.poison_damage = (10 + (float)intelligence * 0.2) * (1 + (float)agility * 0.03);
		}
	}

	pair<bool, int> IceMagic(Unit& target)
	{
		int mana = 50;
		if(alertCount==0)
			return make_pair(1, mana);
		else if (alertCount == -1)
		{
			target.iced = 2;
			current_mp -= mana;
		}

 	}

	pair<bool, int> PutOnBarrier(Unit& target)
	{
		int mana = 20;
		if (alertCount == 0)
			return make_pair(1, mana) ;
		else if (alertCount == -1)
		{
			barrier = 50 + intelligence * 0.1;
			barrierCool = 5;
			current_mp -= mana;
		}
	}
    
	pair<bool, int> Intel(Unit& target)
	{	
		int mana = 20;
		if (alertCount == 0)
			return make_pair(1, mana);
		else if (alertCount == -1)
		{
			intelUpCool = 5;
			current_mp -= mana;
		}
	}

	pair<bool, int> Dart(Unit& target)
	{
		int mana = 30;
		if (alertCount == 0)
			return make_pair(1, mana);
		else if (alertCount == -1)
		{
			int damage = 2 * (attack - armor) * (1 + agility * 0.005);
			if (damage < 0)
				damage = 0;
			target.current_hp -= damage;
			current_mp -= mana;
		}
	}

	pair<bool, int> DamageAbsorb(Unit& target)
	{
		int mana = 20;
		int atk = 15;
		if (alertCount == 0)
			return make_pair(1, mana);
		else if(alertCount == -1)
		if (target.attack <= 0)
			alertCount = 4;
		else if (target.attack <= atk)
		{
			attack += target.attack;
			target.attack = 0;
			current_mp -= mana;
		}
		else
		{
			attack += atk;
			target.attack -= atk;
			current_mp -= mana;
		}

	}

	pair<bool, int>IntelligenceAbsorb(Unit& target)
	{
		int mana = 20;
		int intel = 20;
		if (alertCount == 0)
			return make_pair(1, mana);
		else if (alertCount == -1)
		{
			if (target.intelligence <= 0)
				alertCount = 5;
			else if (target.intelligence <= intel)
			{
				intelligence += target.intelligence;
				target.intelligence = 0;
				current_mp -= mana;
			}
			else
			{
				intelligence += intel;
				target.intelligence -= intel;
				current_mp -= mana;
			}
		}
	}
	
	pair<bool, int> PowerOfGod(Unit& target)
	{
		int mana = 150;
		int damage = intelligence * 0.5 - target.armor;
		if (alertCount == 0)
			return make_pair(1, mana);
		else if (alertCount == -1)
		{
			target.current_hp -= damage;
			current_mp -= mana;
		}
	}

	pair<bool, int> Heal(Unit& target)
	{
		int mana = 50;
		if (alertCount == 0)
			return make_pair(1, mana);
		else if (alertCount == -1)
		{
			current_hp += 30 + intelligence * 0.1;
			if (current_hp > max_hp)
				current_hp = max_hp;
			current_mp -= mana;
		}
	}
	
      };
const int playerInfo[4][7] = { //체력, 마나, 공격력, 지능, 민첩성, 방어도, 체력재생
	300,0,30,0,30,50,30,
	150,150,10,50,50,30,50,
	200, 50, 20, 10, 80, 20, 0,
	20,200,0,200,200,0,0 };

const int enemyInfo[3][7] = {
	100, 50, 0, 200, 10, 20, 0,
	200, 0, 30, 0, 80, 10, 0,
	300, 0, 50, 0, 20, 50, 0,
};

