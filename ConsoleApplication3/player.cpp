#pragma once
#include "player.h"
#include "enemy.h"

class Enemy;

 Player::Player(int hp, int mp, int attack, int intelligence, int agility, int armor, int restore, int id) : Unit(hp, mp, attack, intelligence, agility, armor, restore)
{
	this->playerNumber = id;
	this->current_mp = max_mp;
	temporaryHP = 0;
	temporaryMP = 0;
	temporaryAttack = 0;
	temporaryIntelligence = 0;
	temporaryAgility = 0;
	temporaryArmor = 0;
	temporaryRestore = 0;
}

 Player::Player(Player& player) : Unit(player.basic_hp, player.basic_mp, player.basic_damage, player.basic_intelligence, player.basic_agility, player.basic_armor, player.basic_restore)
{
	playerNumber = player.playerNumber;
	absorbHP = player.absorbHP;
	absorbDamage = player.absorbDamage;
	absorbIntelligence = player.absorbIntelligence;
	max_hp = basic_hp + absorbHP;
	current_hp = max_hp;

	temporaryHP = 0;
	temporaryMP = 0;
	temporaryAttack = 0;
	temporaryIntelligence = 0;
	temporaryAgility = 0;
	temporaryArmor = 0;
	temporaryRestore = 0;

	if (player.playerNumber == 4)
	{
		basic_intelligence = player.basic_intelligence;
		intelligence = player.intelligence;
	}
}

 int Player::PN()
{
	return playerNumber;
}

 void Player::SetPN(int& id)
{
	playerNumber = id;
}

 void Player::SetAbility(const char* item, const char* weapon)
 {
	     max_hp = basic_hp + absorbHP + temporaryHP; 

		 max_mp = basic_mp + temporaryMP;

		 attack = basic_damage + absorbDamage + temporaryAttack;

		 intelligence = basic_intelligence + absorbIntelligence + temporaryIntelligence;

		 agility = basic_agility + temporaryAgility;

		 armor = basic_armor + temporaryArmor;

		 restore = basic_restore + temporaryRestore;

		 if (damageUpCool>0)
		 {
			 attack += basic_damage * 0.5;
		 }

		 if (intelUpCool>0)
		 {
			 intelligence += 50;
		 }

		 for (int i = 0; i < 6; i++)
		 {
			 switch (item[i])
			 {
			 case 1:
				 armor += 20;
				 agility -= 20;
				 break;
			 case 2:
				 intelligence -= 15;
				 break;
			 }
		 }

		 for (int i = 0; i < 2; i++)
		 {
			 switch (weapon[i])
			 {
			 case 1:
				 armor += 10;
				 break;
			 case 2:
				 attack += 15;
				 break;
			 }
		 }

		 if (max_mp < 0)
			 max_mp = 0;

		 if (intelligence < 0)
			 intelligence = 0;

		 if (agility < 0)
			 agility = 0;

} 

 void Player::BuffRemove()
 {
	 --damageUpCool;
	 --intelUpCool;
 };

 int& Player::GameRound()
{
	return gameRound;
}

 pair<bool, int> Player::basic_Attack(Unit& target)
{
	if (playerNumber == 4)
	{
		int damage = intelligence * 0.1;
		if (damage > target.current_hp)
		{
			max_hp += target.current_hp;
			absorbHP += target.current_hp;
			current_hp += target.current_hp;
			pre_hp = current_hp;
			target.current_hp = 0;
		}
		else
		{
			max_hp += damage;
			absorbHP += damage;
			current_hp += damage;
			pre_hp = current_hp;
			target.current_hp -= damage;
		}
	}
	else
	{
		int damage = attack - target.armor;
		if (damage < 0)
			damage = 0;
		target.current_hp -= (damage);
	}
	return make_pair(0, 0);
}

 pair<bool, int> Player::DamageUp(Unit& target)
{
	int hp = 50;
	if (alertCount == 0)
		return make_pair(0, hp);
	else if (alertCount == -1)
	{
		damageUpCool = 5;
		current_hp -= hp;
		pre_hp = current_hp;
	}
	return make_pair(0, 0);
}

 pair<bool, int> Player::DoubleAttack(Unit& target)
{
	 if (alertCount == 0)
		 return make_pair(0, 0);
	 else if (alertCount == -1)
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
	return make_pair(0, 0);
}

 pair<bool, int> Player::Enemy_s_(Unit& target)
{
	if (!enemys)
	{
		int mana = 50;
		if (alertCount == 0)
			return make_pair(1, mana);
		if (alertCount == -1)
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
	else
		return make_pair(0, -1);

  	return make_pair(1, 0);
}

 pair<bool, int> Player::PoisonAttack(Unit& target)
{
	int mana = 30;
	if (alertCount == 0)
		return make_pair(1, mana);
	else if (alertCount == -1)
	{
		target.poison_time = 2;
		target.poison_damage = atoi(CalculateEx(skillCoefficient[2][1] + 2));
		current_mp -= mana;
	}
	return make_pair(1, mana);
}

 pair<bool, int> Player::ignite(Unit& target)
{
	int mana = 30;
	if (alertCount == 0)
		return make_pair(1, mana);
	else if (alertCount == -1)
	{
		target.ignite_time = 2 * (1 + 0.01 * intelligence);
		target.ignite_damage = 30;
	}
	return make_pair(1, mana);
}

 pair<bool, int> Player::ShieldBash(Unit& target)
 {
	 if (alertCount == 0)
		 return make_pair(0, 0);
	 else if (alertCount == -1)
	 {
		 int damage = armor * 2 - target.armor;
		 if (damage < 0)
			 damage = 0;
		 RemoveBarrier(target, damage);
		 temporaryArmor -= 20;
	 }
	 return make_pair(2, 0);
 }

 pair<bool, int> Player::Bite(Unit& target)
 {
	 if (alertCount == 0)
		 return make_pair(0, 0);
	 else if (alertCount == -1)
	 {
		 int damage = attack * 2 - target.armor;
		 if (damage < 0)
			 damage = 0;
		 RemoveBarrier(target, damage);
		 temporaryAttack -= 10;
	 }
	 return make_pair(1, 0);
 }

