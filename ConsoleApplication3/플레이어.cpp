#pragma once
#include "플레이어.h"
#include "적.h"

class Enemy;

pair<bool, int> Player::basic_Attack(Unit& target)
{
	if (playerNumber == 4)
	{
		int damage = intelligence * 0.1;
		if (damage > target.current_hp)
		{
			max_hp += target.current_hp;
			current_hp += target.current_hp;
			target.current_hp = 0;
		}
		else
		{
			target.current_hp -= damage;
			max_hp += damage;
			current_hp += damage;
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
