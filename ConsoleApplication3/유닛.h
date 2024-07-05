#pragma once
#include <random>
#include "Caculate.h"


using namespace std;

#define HP 0x0000001
#define MP 0x0000010


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
	int poison_time = 0;
	int poison_damage = 12;
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
	bool wtf = false;

	int attackPoint = 0;

	friend class Enemy;
	friend class Player;
public:

	Unit(int hp, int mp, int attack, int intelligence, int agility, int armor, int restore);
	int& ReturnHP();
	int& ReturnMP();
	int& SetAlertCount();

	bool GetDamage(bool test);

	int& StunTime();

	void Restoring();

	void ManaCharge();

	void GetPoison();

	int PoisonTime();
	void GetIgnite();

	int IgniteTime();

	void DamageUp();

	bool& TurnReturn();
	int& iced_time();

	int& BarrierCool();

	int& BarrierSize();

	int& IntelCool();

	void SetIntel(int rank);

	int& GetIntelligence();

	pair<const char*, int>GetElement(int number);

	bool Sustained_DPS();

	int& AP();
	void APCharge();

	bool& WTF();

	pair<bool, int> PoisonAttack(Unit& target);

	pair<bool, int> basic_Attack(Unit& target);

	pair<bool, int> Rush(Unit& target);

	pair<bool, int> fireball(Unit& target);

	pair<bool, int> ignite(Unit& target);

	pair<bool, int> IceMagic(Unit& target);

	pair<bool, int> PutOnBarrier(Unit& target);
    
	pair<bool, int> RaiseIntel(Unit& target);

	pair<bool, int> Dart(Unit& target);

	pair<bool, int> DamageAbsorb(Unit& target);

	pair<bool, int>IntelligenceAbsorb(Unit& target);
	
	pair<bool, int> PowerOfGod(Unit& target);

	pair<bool, int> Heal(Unit& target);
	
      };
const int playerInfo[4][7] = { //체력, 마나, 공격력, 지능, 민첩성, 방어도, 체력재생
	300,0,30,0,30,50,30,
	150,150,10,50,50,30,50,
	200, 500, 20, 10, 80, 20, 0,
	20,200,0,200,200,0,0 };

const int enemyInfo[3][7] = {
	100, 50, 0, 200, 10, 20, 0,
	200, 0, 15, 0, 80, 10, 0,
	300, 0, 50, 0, 20, 50, 0,
};

